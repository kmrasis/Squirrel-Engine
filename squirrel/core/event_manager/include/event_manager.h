namespace Squirrel
{
class WindowManager;
class LayerStack;
class EventManager
{
public:
  EventManager(WindowManager* window_manager, LayerStack* layerstack);
  ~EventManager();
  void DispatchEvents();

private:
  WindowManager* window_manager_;
  LayerStack* layerstack_;
};
} // namespace Squirrel
