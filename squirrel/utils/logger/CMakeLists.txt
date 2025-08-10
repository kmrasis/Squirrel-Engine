# Configuration for logger archive
add_library(utils_logger STATIC log-impl.h)
set_target_properties(utils_logger PROPERTIES 
    LINKER_LANGUAGE CXX
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}"
)
target_link_libraries(utils_logger
    spdlog
)
