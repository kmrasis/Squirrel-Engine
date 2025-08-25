add_library(squirrel_window_manager
    src/window_manager.cpp
)
target_compile_definitions(squirrel_window_manager PRIVATE GLFW_INCLUDE_NONE)
target_include_directories(squirrel_window_manager PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_link_libraries(squirrel_window_manager PUBLIC
    utils_logger
    squirrel_events
PRIVATE
    squirrel_input_poller
    dep_glfw
    dep_glad
)
