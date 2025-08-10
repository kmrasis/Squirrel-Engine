add_library(debug_layer STATIC
    src/debug_layer.cpp
)

set_target_properties(debug_layer PROPERTIES
    LINKER_LANGUAGE CXX
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_include_directories(debug_layer PUBLIC
    include/
)

target_link_libraries(debug_layer PUBLIC
    imgui
    utils_logger
    squirrel_layers
)
