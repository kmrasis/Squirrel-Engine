add_library(squirrel SHARED
    main.cpp
)
target_link_libraries(squirrel PUBLIC
    squirrel_application
INTERFACE
    squirrel_layers
)

add_subdirectory(3rdParty)
add_subdirectory(core)
add_subdirectory(utils)
