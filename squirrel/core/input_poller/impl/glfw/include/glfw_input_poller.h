#pragma once
#include "input_poller.h"

class GLFWwindow;
namespace Squirrel
{
class GLFWInputPoller : public InputPoller
{
public:
  GLFWInputPoller(void* window);
  ~GLFWInputPoller();
  virtual bool IsKeyPressed(const int& keycode) override;
  virtual bool IsMouseButtonPressed(const int& button) override;
  virtual pos_t GetCursorPos() override;
  virtual double GetCursorX() override;
  virtual double GetCursorY() override;

private:
  GLFWwindow* window_ = nullptr;
};
} // namespace Squirrel
