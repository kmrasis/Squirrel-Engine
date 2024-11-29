add_library(logger STATIC log.hpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/squirrel/3rdParty/spdlog
    ${CMAKE_BINARY_DIR}/squirrel/3rdParty/spdlog)

target_link_libraries(logger PUBLIC
    spdlog::spdlog
)
