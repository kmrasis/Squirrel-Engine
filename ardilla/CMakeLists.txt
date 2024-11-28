add_executable(ardilla src/ardilla.cpp)

target_include_directories(ardilla PUBLIC
    ${CMAKE_SOURCE_DIR}/squirrel/
)

target_link_libraries(ardilla
    squirrel
)
