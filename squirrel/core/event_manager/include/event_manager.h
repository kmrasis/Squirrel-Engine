#include <memory>

namespace Squirrel
{
class Event;
class WindowManager;
class EventManager
{
public:
  EventManager();
  ~EventManager();

  void Init();
  void DeInit();

  bool IsRunning();

  void DispatchEvents();

private:
  bool is_running = false;
  std::unique_ptr<WindowManager> window_manager_;
};
} // namespace Squirrel
