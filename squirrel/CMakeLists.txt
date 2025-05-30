add_library(squirrel SHARED
    main.cpp
)

target_include_directories(squirrel PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/core/application/include
)

target_include_directories(squirrel INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/core/application/include
    ${CMAKE_CURRENT_LIST_DIR}/core/layers/include
)

target_link_libraries(squirrel
    squirrel_application
    squirrel_layers
)

add_subdirectory(3rdParty)
add_subdirectory(core)
add_subdirectory(utils)
