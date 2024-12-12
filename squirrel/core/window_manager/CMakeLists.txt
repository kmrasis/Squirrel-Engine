# Configuration for glfw archive
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/squirrel/3rdParty/glfw")
set(GLFW_INCLUDE_DIR "${GLFW_DIR}/include")
set(GLFW_LIBRARY "${GLFW_DIR}/libglfw_v3.4.a")

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION "${GLFW_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${GLFW_INCLUDE_DIR}"
)

# Configuration for squirrel_window_manager archive
add_library(squirrel_window_manager
    src/window_manager.cpp
)
set_target_properties(squirrel_window_manager PROPERTIES 
    LINKER_LANGUAGE CXX
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_include_directories(squirrel_window_manager PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(squirrel_window_manager
    PUBLIC
    glfw
    PRIVATE
    squirrel_events
    utils_logger
)
