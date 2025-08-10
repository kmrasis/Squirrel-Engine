# Configuration for spdlog archive
set(SPDLOG_DIR "${CMAKE_SOURCE_DIR}/squirrel/3rdParty/spdlog")
set(SPDLOG_INCLUDE_DIR "${SPDLOG_DIR}/include")
set(SPDLOG_LIBRARY "${SPDLOG_DIR}/libspdlog_v1.15.0.a")

add_library(spdlog STATIC IMPORTED GLOBAL)
set_target_properties(spdlog PROPERTIES
    IMPORTED_LOCATION "${SPDLOG_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${SPDLOG_INCLUDE_DIR}"
)
