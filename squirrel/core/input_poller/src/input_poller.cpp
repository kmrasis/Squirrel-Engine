#include "Config.h"

#ifdef SQUIRREL_USE_GLFW
#include "glfw_input_poller.h"
#endif

namespace Squirrel
{
std::unique_ptr<InputPoller> InputPoller::instance_ = nullptr;
void InputPoller::Init(void* window)
{
  if (!instance_)
  {
#ifdef SQUIRREL_USE_GLFW
    instance_ = std::make_unique<GLFWInputPoller>(window);
#endif
  }
}
void InputPoller::DeInit()
{
  if (instance_)
  {
    instance_.reset();
    instance_ = nullptr;
  }
}
InputPoller& InputPoller::GetInputPoller() { return *instance_; }
} // namespace Squirrel
