# Configuration for squirrel_window_manager archive
add_library(squirrel_window_manager
    src/window_manager.cpp
)
set_target_properties(squirrel_window_manager PROPERTIES 
    LINKER_LANGUAGE CXX
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_compile_definitions(squirrel_window_manager PRIVATE GLFW_INCLUDE_NONE)
target_include_directories(squirrel_window_manager PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(squirrel_window_manager
    glfw
    glad
    squirrel_events
    utils_logger
)
