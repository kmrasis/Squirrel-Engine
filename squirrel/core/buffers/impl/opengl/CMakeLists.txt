add_library(opengl_buffers STATIC
    src/opengl_buffers.cpp
)
target_include_directories(opengl_buffers PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include/"
    "${CMAKE_SOURCE_DIR}/squirrel/core/buffers/include/"
)
target_link_libraries(opengl_buffers PUBLIC
    utils_logger
    dep_glad
)
