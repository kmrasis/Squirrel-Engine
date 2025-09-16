add_library(squirrel_camera STATIC
    "src/camera.cpp"
)
target_include_directories(squirrel_camera PUBLIC
    "include/"
)
target_link_libraries(squirrel_camera PUBLIC
    dep_glm
)
