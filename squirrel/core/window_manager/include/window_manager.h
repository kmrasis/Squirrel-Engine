#include <memory>
#include <queue>

namespace Squirrel
{
class Event;
using EventQueue = std::queue<std::shared_ptr<Event>>;
class WindowManager
{
protected:
  WindowManager();

public:
  virtual ~WindowManager();
  static WindowManager* CreateManager();

  virtual bool CreateWindow(const char* title, const int width, const int height) = 0;

  virtual void GetWindowSize(int* width, int* height)      = 0;
  virtual void GetFrameBufferSize(int* width, int* height) = 0;

  virtual bool ShouldWindowClose()    = 0;
  virtual void SetEventCallbacks()    = 0;
  virtual EventQueue* GetEventQueue() = 0;

  virtual void* GetRawWindow() = 0;
  virtual void CloseWindow()   = 0;
  virtual void PollEvents()    = 0;
  virtual void SwapBuffers()   = 0;

  virtual void SetVSync(const bool& enabled) = 0;
};
} // namespace Squirrel
