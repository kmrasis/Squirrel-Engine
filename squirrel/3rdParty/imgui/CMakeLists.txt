add_library(dep_imgui STATIC
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
)
target_include_directories(dep_imgui PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include/"
)
target_link_libraries(dep_imgui PUBLIC
    dep_glfw
)
