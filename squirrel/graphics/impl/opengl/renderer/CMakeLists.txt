add_library(opengl_renderer STATIC
    src/opengl_renderer.cpp
)
target_include_directories(opengl_renderer PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include"
    "${CMAKE_SOURCE_DIR}/squirrel/graphics/renderer/include/"
)
target_link_libraries(opengl_renderer PUBLIC
    dep_glm
PRIVATE
    utils_logger
    dep_glad
)
