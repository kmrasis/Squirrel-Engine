add_library(opengl_shader STATIC
    src/opengl_shader.cpp
)
target_include_directories(opengl_shader PUBLIC
    "${CMAKE_SOURCE_DIR}/squirrel/core/shader/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
target_link_libraries(opengl_shader PUBLIC
    utils_logger
PRIVATE
    dep_glad
)
