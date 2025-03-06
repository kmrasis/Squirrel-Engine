#include <functional>
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

  void Init(std::function<void(std::shared_ptr<Event>)> ls_callback);
  void DeInit();

  bool IsRunning();

  void DispatchEvents();

private:
  bool is_running = false;
  std::unique_ptr<WindowManager> window_manager_;
  std::function<void(std::shared_ptr<Event>)> layer_stack_callback_;
};
} // namespace Squirrel
