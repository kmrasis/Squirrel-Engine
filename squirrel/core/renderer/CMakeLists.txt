add_library(squirrel_renderer
    src/renderer.cpp
)
target_include_directories(squirrel_renderer PUBLIC
    "include/"
)
target_link_libraries(squirrel_renderer PUBLIC
    squirrel_debug_layer
    squirrel_layers
    squirrel_window_manager
)