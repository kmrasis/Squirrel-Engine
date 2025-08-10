# Configuration for imgui archive
set(IMGUI_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(IMGUI_INCLUDE_DIR "${IMGUI_DIR}")

add_library(imgui STATIC
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    ${IMGUI_INCLUDE_DIR}
)
target_link_libraries(imgui PUBLIC
    glfw
)
