#include <queue>

#include <memory>

class GLFWwindow;
namespace Squirrel
{
class Event;
class WindowProperty;
using EventQueue         = std::queue<std::shared_ptr<Event>>;
using EventQPropertyPair = std::pair<EventQueue, WindowProperty>;
class WindowManager
{
public:
  WindowManager();
  ~WindowManager();

  void Init();

  void DeInit();

  bool IsInitialised();
  bool ShouldWindowClose();

  bool CreateWindow(WindowProperty& props);
  void* GetRawWindow() { return window_; }
  void CloseWindow();

  void SetVSync(const bool& enabled);
  void SetEventCallbacks();
  void PollEvents();
  void StartNewFrame();
  void SwapBuffers();
  EventQueue& GetEventQueue();

private:
  bool is_initialised_ = false;
  GLFWwindow* window_;
  EventQPropertyPair* window_user_pointer_;
};

} // namespace Squirrel
