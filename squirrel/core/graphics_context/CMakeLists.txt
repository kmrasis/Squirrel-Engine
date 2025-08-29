add_library(squirrel_graphics_context STATIC
    src/graphics_context.cpp
)
target_include_directories(squirrel_graphics_context
INTERFACE
    "include/"
)
target_link_libraries(squirrel_graphics_context
PRIVATE
    squirrel_config
    $<$<BOOL:${SQUIRREL_USE_OPENGL}>:opengl_graphics_context>
)

add_subdirectory(impl/opengl)
