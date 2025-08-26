add_library(dep_glad
    src/glad.c
)
target_include_directories(dep_glad PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include"
)
set_target_properties(dep_glad PROPERTIES LINKER_LANGUAGE CXX)
