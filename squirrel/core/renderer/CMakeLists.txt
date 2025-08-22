add_library(squirrel_renderer
    src/renderer.cpp
)
target_include_directories(squirrel_renderer PUBLIC
    "include/"
)
target_link_libraries(squirrel_renderer PUBLIC
    debug_layer
    squirrel_window_manager
)