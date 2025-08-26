add_library(squirrel_event_manager STATIC
    src/event_manager.cpp
)
target_include_directories(squirrel_event_manager PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_link_libraries(squirrel_event_manager
PRIVATE
    squirrel_layers
    squirrel_events
    squirrel_window_manager
)
