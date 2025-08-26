# Configuration for logger archive
add_library(utils_logger INTERFACE
    log-impl.h
)
target_include_directories(utils_logger
INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}"
)
target_link_libraries(utils_logger
INTERFACE
    spdlog
)
set_target_properties(utils_logger PROPERTIES LINKER_LANGUAGE CXX)
