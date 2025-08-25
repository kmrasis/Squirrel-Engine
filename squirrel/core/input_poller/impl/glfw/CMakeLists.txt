add_library(glfw_input_poller STATIC
    src/glfw_input_poller.cpp
)
target_include_directories(glfw_input_poller PUBLIC
    "${CMAKE_SOURCE_DIR}/squirrel/core/input_poller/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
target_link_libraries(glfw_input_poller PUBLIC
    utils_logger
PRIVATE
    glfw
)
