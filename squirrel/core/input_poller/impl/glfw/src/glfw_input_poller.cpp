#include "glfw_input_poller.h"
#include "log-impl.h"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

namespace Squirrel
{
GLFWInputPoller::GLFWInputPoller(void* window)
{
  window_ = (GLFWwindow*)window;
  CONSOLE_INFO("Initialised Glfw Input Poller successfully");
}

GLFWInputPoller::~GLFWInputPoller()
{
  // is_initialised_ = false;
  CONSOLE_INFO("DeInitialised Glfw Input Poller successfully");
}

bool GLFWInputPoller::IsKeyPressed(const int& keycode)
{
  int state = glfwGetKey(window_, keycode);
  return state == GLFW_PRESS;
}

bool GLFWInputPoller::IsMouseButtonPressed(const int& button)
{
  int state = glfwGetMouseButton(window_, button);
  return state == GLFW_PRESS;
}

pos_t GLFWInputPoller::GetCursorPos()
{
  double pos_x, pos_y;
  glfwGetCursorPos(window_, &pos_x, &pos_y);
  return pos_t{pos_x, pos_y};
}

double GLFWInputPoller::GetCursorX()
{
  auto pos = GetCursorPos();
  return pos.x;
}

double GLFWInputPoller::GetCursorY()
{
  auto pos = GetCursorPos();
  return pos.y;
}
} // namespace Squirrel
