add_library(squirrel_events STATIC
    src/event.cpp
    src/appEvent.cpp
    src/keyEvent.cpp
    src/mouseEvent.cpp
    src/windowEvent.cpp
)
target_include_directories(squirrel_events PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
