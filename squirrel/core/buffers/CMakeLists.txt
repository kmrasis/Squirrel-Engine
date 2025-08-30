add_library(squirrel_buffers STATIC
    src/buffers.cpp
)
target_include_directories(squirrel_buffers
INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/include/"
)
target_link_libraries(squirrel_buffers
PRIVATE
    squirrel_config
    $<$<BOOL:${SQUIRREL_USE_OPENGL}>:opengl_buffers>
)

add_subdirectory(impl/opengl)
