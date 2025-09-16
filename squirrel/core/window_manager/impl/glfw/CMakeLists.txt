add_library(glfw_window_manager STATIC
    src/glfw_window_manager.cpp
)
target_include_directories(glfw_window_manager PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include"
    "${CMAKE_SOURCE_DIR}/squirrel/core/window_manager/include/"
)
target_link_libraries(glfw_window_manager PUBLIC
    utils_logger
    squirrel_events
PRIVATE
    squirrel_input_poller
    dep_glfw
    dep_glad
)
