#include "window_manager.h"
#include "log-impl.h"

#include "appEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"
#include "windowEvent.h"
#include "window_property.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

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
  } else
  {
    CONSOLE_INFO("Window Manager initialised successfully");
    is_initialised_ = true;
  }
}

void WindowManager::DeInit()
{
  if (window_)
  {
    CloseWindow();
  }
  glfwTerminate();
  CONSOLE_INFO("Window Manager deinitialised successfully");
}

bool WindowManager::IsInitialised() { return is_initialised_; }

bool WindowManager::CreateWindow(WindowProperty& props)
{
  if (!is_initialised_)
  {
    CONSOLE_ERROR("Failed to Create Window : Window Manager not initialised!");
    return false;
  }

  window_ = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
  CONSOLE_INFO("Window created successfully with Title : {}", props.Title);

  glfwMakeContextCurrent(window_);
  glfwSetWindowUserPointer(window_, &props);
  SetVSync(true);
  SetEventCallbacks();
  return true;
}

void WindowManager::SetVSync(const bool& enabled)
{
  if (enabled)
  {
    glfwSwapInterval(1);
  } else
  {
    glfwSwapInterval(0);
  }
}

void WindowManager::Update()
{
  glfwPollEvents();
  glfwSwapBuffers(window_);
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
                                 WindowEvent window_closed_event(EventType::WindowClose, 0, 0, 0, 0);
                                 pending_event_queue_.push(window_closed_event);
                                 LOG_TRACE("Pushed Event to queue : [{}] ", window_closed_event.Log());
                               });

    // Window Focus/UnFocused Event Callback
    glfwSetWindowFocusCallback(window_,
                               [](GLFWwindow* window, int focused)
                               {
                                 EventType event_type
                                     = (GLFW_TRUE == focused) ? EventType::WindowFocus : EventType::WindowUnfocus;
                                 WindowEvent window_focus_event(event_type, 0, 0, 0, 0);
                                 pending_event_queue_.push(window_focus_event);
                                 LOG_TRACE("Pushed Event to queue : [{}] ", window_focus_event.Log());
                               });

    // Window Resized Event Callback
    glfwSetFramebufferSizeCallback(window_,
                                   [](GLFWwindow* window, int width, int height)
                                   {
                                     WindowEvent window_resize_event(EventType::WindowResize, 0, 0, width, height);
                                     pending_event_queue_.push(window_resize_event);
                                     LOG_TRACE("Pushed Event to queue : [{}] ", window_resize_event.Log());
                                   });

    // Window Moved Event Callback
    glfwSetWindowPosCallback(window_,
                             [](GLFWwindow* window, int xpos, int ypos)
                             {
                               WindowEvent window_moved_event(EventType::WindowMove, xpos, ypos, 0, 0);
                               pending_event_queue_.push(window_moved_event);
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

                         KeyboardEvent key_event(event_type, key, scancode, mods);
                         pending_event_queue_.push(key_event);
                         LOG_TRACE("Pushed Event to queue : [{}] ", key_event.Log());
                       });
  }

  // Set mouse/cursor Event Callbacks
  {

    // Mouse Button pressed/released Event Callback
    glfwSetMouseButtonCallback(window_,
                               [](GLFWwindow* window, int button, int action, int mods)
                               {
                                 EventType event_type = (GLFW_PRESS == action) ? EventType::MouseButtonPress
                                                                               : EventType::MouseButtonRelease;

                                 MouseEvent mouse_event(event_type, 0, 0, 0, 0, button, mods);
                                 pending_event_queue_.push(mouse_event);
                                 LOG_TRACE("Pushed Event to queue : [{}] ", mouse_event.Log());
                               });

    // Mouse cursor moved Event Callback
    glfwSetCursorPosCallback(window_,
                             [](GLFWwindow* window, double xpos, double ypos)
                             {
                               MouseEvent mouse_moved_event(EventType::MouseMove, xpos, ypos, 0, 0, 0, 0);
                               pending_event_queue_.push(mouse_moved_event);
                               LOG_TRACE("Pushed Event to queue : [{}] ", mouse_moved_event.Log());
                             });

    // Mouse/touchpad Scroll Event Callback
    glfwSetScrollCallback(window_,
                          [](GLFWwindow* window, double xoffset, double yoffset)
                          {
                            MouseEvent mouse_scroll_event(EventType::MouseScroll, 0, 0, xoffset, yoffset, 0, 0);
                            pending_event_queue_.push(mouse_scroll_event);
                            LOG_TRACE("Pushed Event to queue : [{}] ", mouse_scroll_event.Log());
                          });
  }

  CONSOLE_INFO("Configured Event Callbacks functions sucessfully!");

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
  glfwDestroyWindow(window_);
  window_ = nullptr;
  CONSOLE_INFO("Window closed successfully");
}

std::queue<Event> pending_event_queue_;
} // namespace Squirrel
