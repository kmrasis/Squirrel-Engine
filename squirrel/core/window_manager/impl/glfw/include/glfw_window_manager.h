#include "window_manager.h"

struct GLFWwindow;
namespace Squirrel
{
class GLFWWindowManager : public WindowManager
{
public:
  GLFWWindowManager();
  ~GLFWWindowManager();

  virtual bool ShouldWindowClose() override;

  virtual bool CreateWindow(const char* title, const int width, const int height) override;
  virtual void* GetRawWindow() override;
  virtual void CloseWindow() override;

  virtual void GetWindowSize(int* width, int* height) override;
  virtual void GetFrameBufferSize(int* width, int* height) override;

  virtual void SetVSync(const bool& enabled) override;
  virtual void SetEventCallbacks() override;
  virtual void PollEvents() override;
  virtual void SwapBuffers() override;
  virtual EventQueue* GetEventQueue() override;

private:
  bool is_glfw_init_ = false;
  ::GLFWwindow* window_;
  EventQueue* event_queue_;
};

} // namespace Squirrel
