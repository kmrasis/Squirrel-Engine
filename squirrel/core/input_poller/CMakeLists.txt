add_library(squirrel_input_poller STATIC
    src/input_poller.cpp
)
target_include_directories(squirrel_input_poller
INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
target_link_libraries(squirrel_input_poller
PRIVATE
    glfw_input_poller
)

add_subdirectory(impl/glfw)
