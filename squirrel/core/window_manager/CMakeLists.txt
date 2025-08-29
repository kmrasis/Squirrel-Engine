add_library(squirrel_window_manager STATIC
    src/window_manager.cpp
)
target_include_directories(squirrel_window_manager
INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_link_libraries(squirrel_window_manager PUBLIC
    squirrel_events
PRIVATE
    squirrel_config
    $<$<BOOL:${SQUIRREL_USE_GLFW}>:glfw_window_manager>
)

add_subdirectory(impl/glfw)
