#include <functional>
#include <memory>

namespace Squirrel
{
class Event;
class WindowManager;
class LayerStack;
class EventManager
{
public:
  EventManager(LayerStack& layerstack);
  ~EventManager();

  void Init();
  void DeInit();

  bool IsInitialised() { return is_initialised_; }
  bool IsRunning();
  void DispatchEvents();

  WindowManager& GetWindowRef();

private:
  bool is_initialised_ = false;
  std::unique_ptr<WindowManager> window_manager_;
  LayerStack& layerstack_;
};
} // namespace Squirrel
