add_library(squirrel SHARED
    core/application.cpp
)

add_subdirectory(logger)

target_include_directories(squirrel PUBLIC
    ${CMAKE_SOURCE_DIR}/squirrel/logger
)

target_link_libraries(squirrel PUBLIC
    logger
)
