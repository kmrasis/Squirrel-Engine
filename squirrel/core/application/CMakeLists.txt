add_library(squirrel_application STATIC
    src/application.cpp
)
target_include_directories(squirrel_application PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_link_libraries(squirrel_application PUBLIC
    utils_logger
    squirrel_layers
PRIVATE
    squirrel_window_manager
    squirrel_event_manager
    squirrel_graphics_context
    squirrel_debug_layer
)
