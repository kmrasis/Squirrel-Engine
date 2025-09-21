add_library(dep_stb STATIC
    stb_image.cpp
)
target_include_directories(dep_stb PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include/"
)
