#include <dlfcn.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "NvInfer.h"
#include "NvInferPlugin.h"

namespace
{
class Logger final : public nvinfer1::ILogger
{
public:
    void log(Severity severity, char const* msg) noexcept override
    {
        if (severity <= Severity::kWARNING)
        {
            std::cerr << "[TensorRT] " << msg << '\n';
        }
    }
};
} // namespace

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <plugin_library_path>\n";
        return EXIT_FAILURE;
    }

    std::string const pluginPath{argv[1]};
    void* handle = dlopen(pluginPath.c_str(), RTLD_LAZY);
    if (handle == nullptr)
    {
        std::cerr << "dlopen failed: " << dlerror() << '\n';
        return EXIT_FAILURE;
    }

    Logger logger;
    initLibNvInferPlugins(&logger, "");

    nvinfer1::IPluginRegistry* registry = getPluginRegistry();
    if (registry == nullptr)
    {
        std::cerr << "Failed to access TensorRT plugin registry.\n";
        dlclose(handle);
        return EXIT_FAILURE;
    }

    auto* creator = registry->getPluginCreator("EfficientNMSCustom_TRT", "1", "");
    if (creator == nullptr)
    {
        std::cerr << "Plugin creator not found: EfficientNMSCustom_TRT v1\n";
        dlclose(handle);
        return EXIT_FAILURE;
    }

    float scoreThreshold{0.25F};
    float iouThreshold{0.65F};
    int32_t maxOutputBoxes{100};
    int32_t backgroundClass{-1};
    int32_t scoreActivation{0};
    int32_t boxCoding{1};

    std::vector<nvinfer1::PluginField> fields{
        nvinfer1::PluginField{"score_threshold", &scoreThreshold, nvinfer1::PluginFieldType::kFLOAT32, 1},
        nvinfer1::PluginField{"iou_threshold", &iouThreshold, nvinfer1::PluginFieldType::kFLOAT32, 1},
        nvinfer1::PluginField{"max_output_boxes", &maxOutputBoxes, nvinfer1::PluginFieldType::kINT32, 1},
        nvinfer1::PluginField{"background_class", &backgroundClass, nvinfer1::PluginFieldType::kINT32, 1},
        nvinfer1::PluginField{"score_activation", &scoreActivation, nvinfer1::PluginFieldType::kINT32, 1},
        nvinfer1::PluginField{"box_coding", &boxCoding, nvinfer1::PluginFieldType::kINT32, 1},
    };
    nvinfer1::PluginFieldCollection fc{};
    fc.nbFields = static_cast<int32_t>(fields.size());
    fc.fields = fields.data();

    auto* plugin = creator->createPlugin("efficient_nms_custom_smoke", &fc);
    if (plugin == nullptr)
    {
        std::cerr << "Plugin creator found, but createPlugin() failed.\n";
        dlclose(handle);
        return EXIT_FAILURE;
    }

    std::cout << "Plugin creator found and createPlugin() succeeded: " << creator->getPluginName() << " v"
              << creator->getPluginVersion() << '\n';

    plugin->destroy();
    dlclose(handle);
    return EXIT_SUCCESS;
}
