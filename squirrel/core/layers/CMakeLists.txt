add_library(squirrel_layers
    src/layerstack.cpp
    src/layer.cpp
)

set_target_properties(squirrel_layers PROPERTIES 
    LINKER_LANGUAGE CXX
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_include_directories(squirrel_layers PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(squirrel_layers
    PRIVATE
    squirrel_events
    utils_logger
)