add_library(dep_glm INTERFACE)
target_include_directories(dep_glm
INTERFACE
	"${CMAKE_CURRENT_LIST_DIR}"
)
