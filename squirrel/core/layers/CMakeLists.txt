add_library(squirrel_layers
    src/layerstack.cpp
    src/layer.cpp
)
target_include_directories(squirrel_layers PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_link_libraries(squirrel_layers PUBLIC
    utils_logger
    squirrel_events
)
