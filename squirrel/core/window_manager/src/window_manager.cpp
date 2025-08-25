#include "window_manager.h"
#include "log-impl.h"

#include "appEvent.h"
#include "input_poller.h"
#include "keyEvent.h"
#include "mouseEvent.h"
#include "windowEvent.h"
#include "window_property.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

/**
 *  Squirrel Engine at this stage supports only single window
 */

namespace Squirrel
{
WindowManager::WindowManager()  = default;
WindowManager::~WindowManager() = default;

void WindowManager::Init()
{
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
  is_initialised_ = true;
  CONSOLE_INFO("Initialised Window Manager successfully");
}

void WindowManager::DeInit()
{
  if (window_)
  {
    CloseWindow();
  }
  delete window_user_pointer_;
  window_user_pointer_ = nullptr;
  glfwTerminate();
  is_initialised_ = false;
  CONSOLE_INFO("DeInitialised Window Manager successfully");
}

bool WindowManager::IsInitialised() { return is_initialised_; }
EventQueue& WindowManager::GetEventQueue() { return window_user_pointer_->first; }

bool WindowManager::ShouldWindowClose()
{
  if (!window_)
  {
    CONSOLE_ERROR("Window Not Created Yet");
    return true; // To Break Any loop dependent on it
  }
  return glfwWindowShouldClose(window_);
}

bool WindowManager::CreateWindow(WindowProperty& props)
{
  if (!is_initialised_)
  {
    CONSOLE_ERROR("Failed to Create Window : Window Manager not initialised!");
    return false;
  }

  window_ = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
  CONSOLE_INFO("Created window successfully with Title : {}", props.Title);

  glfwMakeContextCurrent(window_);
  window_user_pointer_ = new EventQPropertyPair(std::make_pair(EventQueue(), props));
  glfwSetWindowUserPointer(window_, window_user_pointer_);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  if (status == 1)
  {
    CONSOLE_INFO("Initialised GLAD successfully");
  }

  InputPoller::Init(window_);
  SetVSync(true);
  SetEventCallbacks();
  return true;
}

void WindowManager::SetVSync(const bool& enabled)
{
  CONSOLE_INFO("Setting VSync [{}]", (enabled ? "enable" : "disable"));
  if (enabled)
  {
    glfwSwapInterval(1);
  } else
  {
    glfwSwapInterval(0);
  }
}

void WindowManager::PollEvents()
{
  LOG_DEBUG("Polling Events");
  glfwPollEvents();
}

void WindowManager::SwapBuffers()
{
  LOG_DEBUG("Swapping glfw Buffers");
  glfwSwapBuffers(window_);
}
void WindowManager::StartNewFrame()
{
  LOG_DEBUG("Clear screen to start new frame");
  // Specify viewing area to be used by OpenGL:
  // Bottom Left (0,0) to Top Right (width, Height)
  int buff_width, buff_height;
  glfwGetFramebufferSize(window_, &buff_width, &buff_height);
  glViewport(0, 0, buff_width, buff_height);

  // Clear back buffer by assigning new color to it
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void WindowManager::SetEventCallbacks()
{
  // Set Error Callback
  glfwSetErrorCallback([](int error_code, const char* description)
                       { CONSOLE_ERROR("GLFW Error ({}) : {}", error_code, description); });

  // Set Window Event Callbacks
  {
    // Window Close Event Callback
    glfwSetWindowCloseCallback(window_,
                               [](GLFWwindow* window)
                               {
                                 EventQueue& pending_event_queue_
                                     = static_cast<EventQPropertyPair*>(glfwGetWindowUserPointer(window))->first;

                                 WindowCloseEvent window_closed_event(EventType::WindowClose);
                                 pending_event_queue_.push(std::make_shared<WindowCloseEvent>(window_closed_event));
                                 LOG_TRACE("Pushed Event to queue : [{}] ", window_closed_event.Log());
                               });

    // Window Focus/UnFocused Event Callback
    glfwSetWindowFocusCallback(window_,
                               [](GLFWwindow* window, int focused)
                               {
                                 EventQueue& pending_event_queue_
                                     = static_cast<EventQPropertyPair*>(glfwGetWindowUserPointer(window))->first;
                                 EventType event_type
                                     = (GLFW_TRUE == focused) ? EventType::WindowFocus : EventType::WindowUnfocus;
                                 WindowFocusEvent window_focus_event(event_type);
                                 pending_event_queue_.push(std::make_shared<WindowFocusEvent>(window_focus_event));
                                 LOG_TRACE("Pushed Event to queue : [{}] ", window_focus_event.Log());
                               });

    // Window Resized Event Callback
    glfwSetFramebufferSizeCallback(
        window_,
        [](GLFWwindow* window, int width, int height)
        {
          EventQueue& pending_event_queue_ = static_cast<EventQPropertyPair*>(glfwGetWindowUserPointer(window))->first;
          WindowResizeEvent window_resize_event(EventType::WindowResize, width, height);
          pending_event_queue_.push(std::make_shared<WindowResizeEvent>(window_resize_event));
          LOG_TRACE("Pushed Event to queue : [{}] ", window_resize_event.Log());
        });

    // Window Moved Event Callback
    glfwSetWindowPosCallback(window_,
                             [](GLFWwindow* window, int xpos, int ypos)
                             {
                               EventQueue& pending_event_queue_
                                   = static_cast<EventQPropertyPair*>(glfwGetWindowUserPointer(window))->first;
                               WindowMoveEvent window_moved_event(EventType::WindowMove, xpos, ypos);
                               pending_event_queue_.push(std::make_shared<WindowMoveEvent>(window_moved_event));
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
                         EventQueue& pending_event_queue_
                             = static_cast<EventQPropertyPair*>(glfwGetWindowUserPointer(window))->first;
                         KeyPressEvent key_event(event_type, key, scancode, mods);
                         pending_event_queue_.push(std::make_shared<KeyPressEvent>(key_event));
                         LOG_TRACE("Pushed Event to queue : [{}] ", key_event.Log());
                       });

    // Key typed/char input
    glfwSetCharCallback(window_,
                        [](GLFWwindow* window, unsigned int c)
                        {
                          EventType event_type = EventType::KeyType;
                          EventQueue& pending_event_queue_
                              = static_cast<EventQPropertyPair*>(glfwGetWindowUserPointer(window))->first;
                          KeyTypeEvent key_type_event(event_type, c);
                          pending_event_queue_.push(std::make_shared<KeyTypeEvent>(key_type_event));
                          LOG_TRACE("Pushed Event to queue : [{}] ", key_type_event.Log());
                        });
  }

  // Set mouse/cursor Event Callbacks
  {

    // Mouse Button pressed/released Event Callback
    glfwSetMouseButtonCallback(
        window_,
        [](GLFWwindow* window, int button, int action, int mods)
        {
          EventType event_type = (GLFW_PRESS == action) ? EventType::MouseButtonPress : EventType::MouseButtonRelease;
          EventQueue& pending_event_queue_ = static_cast<EventQPropertyPair*>(glfwGetWindowUserPointer(window))->first;
          MouseButtonEvent mouse_event(event_type, button, mods);
          pending_event_queue_.push(std::make_shared<MouseButtonEvent>(mouse_event));
          LOG_TRACE("Pushed Event to queue : [{}] ", mouse_event.Log());
        });

    // Mouse cursor moved Event Callback
    glfwSetCursorPosCallback(window_,
                             [](GLFWwindow* window, double xpos, double ypos)
                             {
                               EventQueue& pending_event_queue_
                                   = static_cast<EventQPropertyPair*>(glfwGetWindowUserPointer(window))->first;
                               MouseMoveEvent mouse_moved_event(EventType::MouseMove, xpos, ypos);
                               pending_event_queue_.push(std::make_shared<MouseMoveEvent>(mouse_moved_event));
                               LOG_TRACE("Pushed Event to queue : [{}] ", mouse_moved_event.Log());
                             });

    // Mouse/touchpad Scroll Event Callback
    glfwSetScrollCallback(window_,
                          [](GLFWwindow* window, double xoffset, double yoffset)
                          {
                            EventQueue& pending_event_queue_
                                = static_cast<EventQPropertyPair*>(glfwGetWindowUserPointer(window))->first;
                            MouseScrollEvent mouse_scroll_event(EventType::MouseScroll, xoffset, yoffset);
                            pending_event_queue_.push(std::make_shared<MouseScrollEvent>(mouse_scroll_event));
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

void WindowManager::CloseWindow()
{
  InputPoller::DeInit();
  glfwDestroyWindow(window_);
  window_ = nullptr;
  CONSOLE_INFO("Closed window successfully");
}
} // namespace Squirrel
