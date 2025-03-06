#include <queue>

#include <memory>

class GLFWwindow;
namespace Squirrel
{
class Event;
class WindowProperty;
class WindowManager
{
public:
  WindowManager();
  ~WindowManager();

  void Init();

  void DeInit();

  bool IsInitialised();

  bool CreateWindow(WindowProperty& props);

  void CloseWindow();

  void SetVSync(const bool& enabled);

  void Update();

  void SetEventCallbacks();

private:
  bool is_initialised_ = false;
  GLFWwindow* window_;
};

extern std::queue<std::shared_ptr<Event>> pending_event_queue_;
} // namespace Squirrel
