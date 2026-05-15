file(GLOB EFFICIENT_NMS_CUSTOM_SRCS CONFIGURE_DEPENDS *.cpp *.cu)

set(VENDORED_TRT_OSS_ROOT "${PROJECT_SOURCE_DIR}/third_party/tensorrt_oss")
if(NOT TENSORRT_OSS_ROOT)
    set(TENSORRT_OSS_ROOT "${VENDORED_TRT_OSS_ROOT}")
endif()

set(TRT_OSS_PLUGIN_DIR "${TENSORRT_OSS_ROOT}/plugin")
set(TRT_OSS_COMMON_DIR "${TRT_OSS_PLUGIN_DIR}/common")

if(NOT EXISTS "${TRT_OSS_COMMON_DIR}/plugin.h")
    message(FATAL_ERROR "Missing TensorRT OSS plugin common headers. Expected ${TRT_OSS_COMMON_DIR}/plugin.h (default vendored path: ${VENDORED_TRT_OSS_ROOT}).")
endif()

add_library(efficient_nms_custom SHARED ${EFFICIENT_NMS_CUSTOM_SRCS})

target_include_directories(efficient_nms_custom
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${TENSORRT_INCLUDE_DIR}
        ${TRT_OSS_PLUGIN_DIR}
)

target_link_libraries(efficient_nms_custom
    PRIVATE
        ${NVINFER_LIB}
        ${NVINFER_PLUGIN_LIB}
        CUDA::cudart
)

set_target_properties(efficient_nms_custom PROPERTIES
    OUTPUT_NAME efficient_nms_custom
)
