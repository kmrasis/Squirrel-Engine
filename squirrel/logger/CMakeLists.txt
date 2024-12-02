# Configuration for spdlog archive
set(SPDLOG_DIR "${CMAKE_SOURCE_DIR}/squirrel/3rdParty/spdlog")
set(SPDLOG_INCLUDE_DIR "${SPDLOG_DIR}/include")
set(SPDLOG_LIBRARY "${SPDLOG_DIR}/libspdlog_v1.15.0.a")

add_library(spdlog STATIC IMPORTED)
set_target_properties(spdlog PROPERTIES
    IMPORTED_LOCATION "${SPDLOG_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${SPDLOG_INCLUDE_DIR}"
)

# Configuration for logger archive
add_library(logger STATIC log.hpp)
set_target_properties(logger PROPERTIES 
    LINKER_LANGUAGE CXX
)
target_link_libraries(logger PUBLIC
    spdlog
)
