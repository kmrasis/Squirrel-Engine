add_library(squirrel_renderer STATIC
    src/renderer.cpp
)
target_include_directories(squirrel_renderer
INTERFACE
    "include/"
)
target_link_libraries(squirrel_renderer PUBLIC
    squirrel_graphics
PRIVATE
    squirrel_config
    $<$<BOOL:${SQUIRREL_USE_OPENGL}>:opengl_renderer>
)
