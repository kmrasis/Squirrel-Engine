add_library(squirrel_debug_layer STATIC
    src/debug_layer.cpp
)
target_include_directories(squirrel_debug_layer PUBLIC
    "include/"
)
target_link_libraries(squirrel_debug_layer PUBLIC
    squirrel_events
PRIVATE
    dep_imgui
    squirrel_layers
    squirrel_graphics
    squirrel_camera
)
