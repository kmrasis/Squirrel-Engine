add_library(debug_layer STATIC
    src/debug_layer.cpp
)
target_include_directories(debug_layer PUBLIC
    "include/"
)
target_link_libraries(debug_layer PUBLIC
    squirrel_events
PRIVATE
    imgui
    squirrel_layers
)
