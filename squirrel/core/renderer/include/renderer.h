
namespace Squirrel
{
class LayerStack;
class WindowManager;
class DebugLayer;
class Renderer
{
public:
  Renderer(WindowManager& window_manager, LayerStack& layerstack, DebugLayer& debug_layer);
  ~Renderer();

  void Init();
  void DeInit();
  void StartNewFrame();
  void RenderLayers();
  void ImGuiRenderLayers();
  void DrawImGuiLayerFrame();
  void SwapBuffers();
  bool IsInitialised() { return is_initialised_; }

private:
  bool is_initialised_ = false;
  LayerStack& layerstack_;
  WindowManager& window_manager_;
  DebugLayer& debug_layer_;
};
} // namespace Squirrel
