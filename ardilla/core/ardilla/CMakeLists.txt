add_executable(ardilla src/ardilla.cpp)

target_include_directories(ardilla PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/
)

target_link_libraries(ardilla
    squirrel
)
