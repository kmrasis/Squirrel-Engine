class GLFWwindow;
namespace Squirrel
{
class WindowProperty;
class WindowManager
{
public:
  WindowManager();
  ~WindowManager();

  void Init();

  void DeInit();

  bool CreateWindow(WindowProperty& props);

  void CloseWindow();

  void SetVSync(const bool& enabled);

  void OnUpdate();

private:
  bool is_initialised_ = false;
  GLFWwindow* window_;
};
} // namespace Squirrel
