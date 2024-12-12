add_library(squirrel_event_manager src/event_manager.cpp)
target_include_directories(squirrel_event_manager PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
set_target_properties(squirrel_event_manager PROPERTIES 
    LINKER_LANGUAGE CXX
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_link_libraries(squirrel_event_manager
    PUBLIC
    utils_logger
    squirrel_events
    squirrel_window_manager
)
