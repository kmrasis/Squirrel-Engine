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
add_library(utils_logger STATIC log-impl.h)
set_target_properties(utils_logger PROPERTIES 
    LINKER_LANGUAGE CXX
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}"
)
target_link_libraries(utils_logger PUBLIC
    spdlog
)
