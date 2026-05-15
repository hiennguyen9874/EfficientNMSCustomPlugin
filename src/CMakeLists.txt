add_subdirectory(plugins)

if(BUILD_PLUGIN_REGISTRY_CHECK_APP)
    add_subdirectory(apps)
endif()
