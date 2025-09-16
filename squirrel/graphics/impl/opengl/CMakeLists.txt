add_library(opengl_graphics STATIC
    opengl_buffer.hpp
    opengl_mesh.hpp
    opengl_pipeline.hpp
    opengl_shader.hpp
)
set_target_properties(opengl_graphics PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(opengl_graphics PUBLIC
    "${CMAKE_SOURCE_DIR}/squirrel/graphics"
    "${CMAKE_CURRENT_LIST_DIR}"
)
target_link_libraries(opengl_graphics PUBLIC
    utils_logger
    dep_glad
)

add_subdirectory(renderer)
