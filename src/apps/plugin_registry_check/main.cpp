#include <dlfcn.h>

#include <cstdlib>
#include <iostream>
#include <string>

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

    std::cout << "Plugin creator found: " << creator->getPluginName() << " v" << creator->getPluginVersion() << '\n';
    dlclose(handle);
    return EXIT_SUCCESS;
}
