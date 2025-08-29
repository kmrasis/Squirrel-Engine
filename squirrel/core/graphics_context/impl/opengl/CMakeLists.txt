add_library(opengl_graphics_context STATIC
    src/opengl_graphics_context.cpp
)
target_include_directories(opengl_graphics_context PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include"
    "${CMAKE_SOURCE_DIR}/squirrel/core/graphics_context/include/"
)
target_link_libraries(opengl_graphics_context
PRIVATE
    utils_logger
    dep_glad
)
