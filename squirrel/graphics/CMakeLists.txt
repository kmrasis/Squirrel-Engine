add_library(squirrel_graphics STATIC
    src/device.cpp
)
target_include_directories(squirrel_graphics PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include/"
)
target_link_libraries(squirrel_graphics PUBLIC
    dep_glm
PRIVATE
    opengl_graphics
)

add_subdirectory(renderer)
add_subdirectory(impl/opengl)
