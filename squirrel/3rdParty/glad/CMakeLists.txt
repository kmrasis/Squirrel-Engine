# Configuration for glad archive
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/squirrel/3rdParty/glad")
set(GLAD_INCLUDE_DIR "${GLAD_DIR}/include")

# Configuration for glad archive
add_library(glad
    src/glad.c
)
set_target_properties(glad PROPERTIES 
    LINKER_LANGUAGE CXX
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
