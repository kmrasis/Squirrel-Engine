add_library(squirrel SHARED
    main.cpp
)

set_target_properties(squirrel PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/core/application/include"
)

target_include_directories(squirrel PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/core/application/include
)

target_link_libraries(squirrel PUBLIC
    squirrel_application
)

add_subdirectory(core)
add_subdirectory(utils)
