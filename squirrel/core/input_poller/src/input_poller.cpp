#include "glfw_input_poller.h"

namespace Squirrel
{
std::unique_ptr<InputPoller> InputPoller::instance_ = nullptr;
void InputPoller::Init(void* window)
{
  if (!instance_)
  {
    instance_ = std::make_unique<GLFWInputPoller>(window);
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
