#include "glfw_window_manager.h"
#include "log-impl.h"

#include "appEvent.h"
#include "input_poller.h"
#include "keyEvent.h"
#include "mouseEvent.h"
#include "windowEvent.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace Squirrel
{
GLFWWindowManager::GLFWWindowManager()
{
  // Set Error Callback
  glfwSetErrorCallback([](int error_code, const char* description)
                       { CONSOLE_ERROR("GLFW Error ({}) : {}", error_code, description); });
  if (!glfwInit())
  {
    CONSOLE_ERROR("Failed to initialise Window Manager!");
    return;
  }

  // Tell glfw what OpenGL version we want to use: here 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Tell glfw we're going to use CORE OpenGL profile i.e, only modern functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  is_glfw_init_ = true;
  CONSOLE_INFO("Initialised Window Manager successfully");
}

GLFWWindowManager::~GLFWWindowManager()
{
  CloseWindow();
  if (event_queue_)
  {
    delete event_queue_;
    event_queue_ = nullptr;
  }
  glfwTerminate();
  CONSOLE_INFO("DeInitialised Window Manager successfully");
}

EventQueue* GLFWWindowManager::GetEventQueue() { return event_queue_; }
bool GLFWWindowManager::ShouldWindowClose()
{
  if (!window_)
  {
    CONSOLE_ERROR("Window Not Created Yet");
    return true; // To Break Any loop dependent on it
  }
  return glfwWindowShouldClose(window_);
}

bool GLFWWindowManager::CreateWindow(const char* title, const int width, const int height)
{
  if (!is_glfw_init_)
  {
    CONSOLE_ERROR("Failed to Create Window : GLFW not initialised!");
    return false;
  }

  window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window_)
  {
    // Error callback should log the error msg
    return false;
  }
  CONSOLE_INFO("Created window successfully with Title : {}", title);

  glfwMakeContextCurrent(window_);
  event_queue_ = new EventQueue();
  glfwSetWindowUserPointer(window_, event_queue_);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    CONSOLE_ERROR("Failed to Load OpenGL functions");
    return false;
  }

  InputPoller::Init(window_);
  SetVSync(true);
  return true;
}

void GLFWWindowManager::CloseWindow()
{
  if (window_)
  {
    InputPoller::DeInit();
    glfwDestroyWindow(window_);
    window_ = nullptr;
    CONSOLE_INFO("Closed window successfully");
  }
}

void* GLFWWindowManager::GetRawWindow() { return window_; }
void GLFWWindowManager::GetWindowSize(int* width, int* height) { glfwGetWindowSize(window_, width, height); }
void GLFWWindowManager::GetFrameBufferSize(int* width, int* height) { glfwGetFramebufferSize(window_, width, height); }

void GLFWWindowManager::SetVSync(const bool& enabled)
{
  CONSOLE_INFO("Setting VSync [{}]", (enabled ? "enable" : "disable"));
  glfwSwapInterval(enabled ? 1 : 0);
}

void GLFWWindowManager::PollEvents()
{
  LOG_DEBUG("Polling Events");
  glfwPollEvents();
}

void GLFWWindowManager::SwapBuffers()
{
  LOG_DEBUG("Swapping glfw Buffers");
  glfwSwapBuffers(window_);
}

void GLFWWindowManager::SetEventCallbacks()
{
  // Set Window Event Callbacks
  {
    // Window Close Event Callback
    glfwSetWindowCloseCallback(window_,
                               [](GLFWwindow* window)
                               {
                                 EventQueue* event_queue_ = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
                                 if (!event_queue_)
                                 {
                                   return;
                                 }

                                 WindowCloseEvent window_closed_event(EventType::WindowClose);
                                 event_queue_->push(std::make_shared<WindowCloseEvent>(window_closed_event));
                                 LOG_TRACE("Pushed Event to queue : [{}] ", window_closed_event.Log());
                               });

    // Window Focus/UnFocused Event Callback
    glfwSetWindowFocusCallback(window_,
                               [](GLFWwindow* window, int focused)
                               {
                                 EventQueue* event_queue_ = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
                                 if (!event_queue_)
                                 {
                                   return;
                                 }
                                 EventType event_type
                                     = (GLFW_TRUE == focused) ? EventType::WindowFocus : EventType::WindowUnfocus;
                                 WindowFocusEvent window_focus_event(event_type);
                                 event_queue_->push(std::make_shared<WindowFocusEvent>(window_focus_event));
                                 LOG_TRACE("Pushed Event to queue : [{}] ", window_focus_event.Log());
                               });

    // Window Resized Event Callback
    glfwSetFramebufferSizeCallback(window_,
                                   [](GLFWwindow* window, int width, int height)
                                   {
                                     EventQueue* event_queue_
                                         = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
                                     if (!event_queue_)
                                     {
                                       return;
                                     }
                                     WindowResizeEvent window_resize_event(EventType::WindowResize, width, height);
                                     event_queue_->push(std::make_shared<WindowResizeEvent>(window_resize_event));
                                     LOG_TRACE("Pushed Event to queue : [{}] ", window_resize_event.Log());
                                   });

    // Window Moved Event Callback
    glfwSetWindowPosCallback(window_,
                             [](GLFWwindow* window, int xpos, int ypos)
                             {
                               EventQueue* event_queue_ = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
                               if (!event_queue_)
                               {
                                 return;
                               }
                               WindowMoveEvent window_moved_event(EventType::WindowMove, xpos, ypos);
                               event_queue_->push(std::make_shared<WindowMoveEvent>(window_moved_event));
                               LOG_TRACE("Pushed Event to queue : [{}] ", window_moved_event.Log());
                             });
  }

  // Set Keyboard Event Callbacks
  {
    // Key Pressed/released/repeated Event Callback
    glfwSetKeyCallback(window_,
                       [](GLFWwindow* window, int key, int scancode, int action, int mods)
                       {
                         EventType event_type = EventType::Unknown;
                         switch (action)
                         {
                           case GLFW_PRESS:
                             event_type = EventType::KeyPress;
                             break;
                           case GLFW_RELEASE:
                             event_type = EventType::KeyRelease;
                             break;
                           case GLFW_REPEAT:
                             event_type = EventType::KeyRepeat;
                             break;

                           default:
                             break;
                         }
                         EventQueue* event_queue_ = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
                         if (!event_queue_)
                         {
                           return;
                         }
                         KeyPressEvent key_event(event_type, key, scancode, mods);
                         event_queue_->push(std::make_shared<KeyPressEvent>(key_event));
                         LOG_TRACE("Pushed Event to queue : [{}] ", key_event.Log());
                       });

    // Key typed/char input
    glfwSetCharCallback(window_,
                        [](GLFWwindow* window, unsigned int c)
                        {
                          EventType event_type     = EventType::KeyType;
                          EventQueue* event_queue_ = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
                          if (!event_queue_)
                          {
                            return;
                          }
                          KeyTypeEvent key_type_event(event_type, c);
                          event_queue_->push(std::make_shared<KeyTypeEvent>(key_type_event));
                          LOG_TRACE("Pushed Event to queue : [{}] ", key_type_event.Log());
                        });
  }

  // Set mouse/cursor Event Callbacks
  {

    // Mouse Button pressed/released Event Callback
    glfwSetMouseButtonCallback(window_,
                               [](GLFWwindow* window, int button, int action, int mods)
                               {
                                 EventType event_type     = (GLFW_PRESS == action) ? EventType::MouseButtonPress
                                                                                   : EventType::MouseButtonRelease;
                                 EventQueue* event_queue_ = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
                                 if (!event_queue_)
                                 {
                                   return;
                                 }
                                 MouseButtonEvent mouse_event(event_type, button, mods);
                                 event_queue_->push(std::make_shared<MouseButtonEvent>(mouse_event));
                                 LOG_TRACE("Pushed Event to queue : [{}] ", mouse_event.Log());
                               });

    // Mouse cursor moved Event Callback
    glfwSetCursorPosCallback(window_,
                             [](GLFWwindow* window, double xpos, double ypos)
                             {
                               EventQueue* event_queue_ = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
                               if (!event_queue_)
                               {
                                 return;
                               }
                               MouseMoveEvent mouse_moved_event(EventType::MouseMove, xpos, ypos);
                               event_queue_->push(std::make_shared<MouseMoveEvent>(mouse_moved_event));
                               LOG_TRACE("Pushed Event to queue : [{}] ", mouse_moved_event.Log());
                             });

    // Mouse/touchpad Scroll Event Callback
    glfwSetScrollCallback(window_,
                          [](GLFWwindow* window, double xoffset, double yoffset)
                          {
                            EventQueue* event_queue_ = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
                            if (!event_queue_)
                            {
                              return;
                            }
                            MouseScrollEvent mouse_scroll_event(EventType::MouseScroll, xoffset, yoffset);
                            event_queue_->push(std::make_shared<MouseScrollEvent>(mouse_scroll_event));
                            LOG_TRACE("Pushed Event to queue : [{}] ", mouse_scroll_event.Log());
                          });
  }

  CONSOLE_INFO("Configured Event Callbacks functions successfully!");

  /**
   * @todo Implement rest of the event callback functions
   *
   * Monitor is connected/disconnected from the system
   *   glfwSetMonitorCallback([](GLFWmonitor* monitor, int event) {});
   *
   * Joystick Connected/Disconnected Event Callback
   *   glfwSetJoystickCallback([](int jid, int event) {});
   *
   * Window refreshed Event Callback
   *   glfwSetWindowRefreshCallback(window_, [](GLFWwindow* window) {});
   *
   * Window Iconcified/Restored Event Callback
   *   glfwSetWindowIconifyCallback(window_, [](GLFWwindow* window, int iconified) {});
   *
   * Window maximized/restored Event Callback
   *   glfwSetWindowMaximizeCallback(window_, [](GLFWwindow* window, int maximized) {});
   *
   * Window zoom/unzoom Event Callback
   *   glfwSetWindowContentScaleCallback(window_, [](GLFWwindow* window, float xscale, float yscale) {});
   *
   * Unicode char input Event Callback
   *   glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int codepoint) {});
   *
   * Unicode char input (regardless of modifier key) Event Callback
   *   glfwSetCharModsCallback(window_, [](GLFWwindow* window, unsigned int codepoint, int mods) {});
   *
   * Mouse cursor entered/exited content area (hover) Event Callback
   *   glfwSetCursorEnterCallback(window_, [](GLFWwindow* window, int entered) {});
   *
   * Drag and drop Event Callback
   *   glfwSetDropCallback(window_, [](GLFWwindow* window, int path_count, const char* paths[]) {});
   */
}
} // namespace Squirrel
