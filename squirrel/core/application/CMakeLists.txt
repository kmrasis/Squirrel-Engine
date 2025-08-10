add_library(squirrel_application STATIC
    src/application.cpp
)
target_include_directories(squirrel_application PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_SOURCE_DIR}/squirrel/core/events/include
    
)
target_link_libraries(squirrel_application
    utils_logger
    squirrel_event_manager
    squirrel_layers
    debug_layer
)
