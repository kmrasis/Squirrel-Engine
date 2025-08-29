add_library(squirrel SHARED
    main.cpp
)
target_link_libraries(squirrel PUBLIC
    squirrel_application
INTERFACE
    squirrel_layers
    squirrel_input_poller
    dep_imgui
    dep_glm
)

if(WIN32)
    set(WINDOWS 1)
    set(LINUX 0)
elseif(UNIX AND NOT APPLE)
    set(LINUX 1)
    set(WINDOWS 0)
endif()

if(WINDOWS OR LINUX)
    set(SQUIRREL_USE_GLFW 1)
    set(SQUIRREL_USE_OPENGL 1)
endif()

# Generate config file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.ini"
    "${CMAKE_CURRENT_BINARY_DIR}/Config.h"
)
add_library(squirrel_config INTERFACE)
target_include_directories(squirrel_config
INTERFACE
    "${CMAKE_CURRENT_BINARY_DIR}"
)


add_subdirectory(3rdParty)
add_subdirectory(core)
add_subdirectory(utils)
