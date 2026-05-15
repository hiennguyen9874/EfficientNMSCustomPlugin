add_executable(check_efficient_nms_plugin main.cpp)

target_include_directories(check_efficient_nms_plugin PRIVATE ${TENSORRT_INCLUDE_DIR} ${CUDAToolkit_INCLUDE_DIRS})

target_link_libraries(check_efficient_nms_plugin PRIVATE ${NVINFER_LIB} ${NVINFER_PLUGIN_LIB} CUDA::cudart ${CMAKE_DL_LIBS})
