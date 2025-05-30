add_library(ardilla_layers
    src/layer_example.cpp
)

target_include_directories(ardilla_layers PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_include_directories(ardilla_layers INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(ardilla_layers
    squirrel_layers
    utils_logger
    squirrel_events
)

