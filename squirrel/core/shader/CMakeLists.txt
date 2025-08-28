add_library(squirrel_shader STATIC
    src/shader.cpp
)
target_include_directories(squirrel_shader
INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/include/"
)
target_link_libraries(squirrel_shader
PRIVATE
    opengl_shader
)

add_subdirectory(impl/opengl)
