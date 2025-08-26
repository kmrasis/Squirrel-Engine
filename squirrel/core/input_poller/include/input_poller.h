#pragma once
#include <memory>
namespace Squirrel
{
using pos_t = struct
{
  double x;
  double y;
};
class InputPoller
{
protected:
  InputPoller() = default;

public:
  virtual ~InputPoller() = default;
  static void Init(void* window);
  static void DeInit();
  static InputPoller& GetInputPoller();

  virtual bool IsKeyPressed(const int& keycode)        = 0;
  virtual bool IsMouseButtonPressed(const int& button) = 0;
  virtual pos_t GetCursorPos()                         = 0;
  virtual double GetCursorX()                          = 0;
  virtual double GetCursorY()                          = 0;

private:
  static std::unique_ptr<InputPoller> instance_;
};
} // namespace Squirrel
