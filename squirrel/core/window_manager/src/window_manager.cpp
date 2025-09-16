#include "Config.h"

#ifdef SQUIRREL_USE_GLFW
#include "glfw_window_manager.h"
#endif

namespace Squirrel
{
WindowManager::WindowManager()  = default;
WindowManager::~WindowManager() = default;
WindowManager* WindowManager::CreateManager()
{
#ifdef SQUIRREL_USE_GLFW
  return new GLFWWindowManager();
#else
  return nullptr;
#endif
}
} // namespace Squirrel
