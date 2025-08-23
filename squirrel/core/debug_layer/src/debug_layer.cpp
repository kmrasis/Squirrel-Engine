#include "debug_layer.h"
#include "log-impl.h"

#include "imgui_impl_glfw.cpp"
#include "imgui_impl_opengl3.h"

#include "appEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"
#include "windowEvent.h"

Squirrel::DebugLayer::DebugLayer()
    : Layer("DebugLayer"){};
Squirrel::DebugLayer::~DebugLayer() = default;

void Squirrel::DebugLayer::Init(void* window)
{
  window_ = (GLFWwindow*)window;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  ImGuiIO& io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  is_initialised_ = ImGui_ImplOpenGL3_Init("#version 410");
  is_initialised_ = is_initialised_ && ImGui_ImplGlfw_InitForOpenGL(window_, false);
  if (!is_initialised_)
  {
    CONSOLE_ERROR("Failed to initialise ImGUI");
    return;
  }
  CONSOLE_INFO("Initialised ImGUI Successfully");
}
void Squirrel::DebugLayer::DeInit()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  is_initialised_ = false;
  CONSOLE_INFO("DeInitialised ImGUI Successfully");
}
void Squirrel::DebugLayer::Attach() {}
void Squirrel::DebugLayer::Detach() {}
void Squirrel::DebugLayer::Update() {}
void Squirrel::DebugLayer::StartNewFrame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  LOG_DEBUG("Started New ImGUI Frame");
}

void Squirrel::DebugLayer::Render() {}
void Squirrel::DebugLayer::ImGuiRender()
{
  LOG_DEBUG("Show demo ImGUI Window");
  ImGui::ShowDemoWindow();
}
void Squirrel::DebugLayer::DrawFrame()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  LOG_DEBUG("Rendered ImGUI Frame");
}
void Squirrel::DebugLayer::HandleEvent(const std::shared_ptr<Event> event)
{
  LOG_TRACE("SQUIRREL :: Received event in layer : {}. EVENT DATA: [{}]", debug_name_, event->Log());
  switch (event->GetEventType())
  {
    case EventType::WindowFocus:
    case EventType::WindowUnfocus:
      ProcessWindowFocusEvent(std::static_pointer_cast<WindowFocusEvent>(event));
      break;

    case EventType::KeyPress:
    case EventType::KeyRepeat:
    case EventType::KeyRelease:
      ProcessKeyPressEvent(std::static_pointer_cast<KeyPressEvent>(event));
      break;

    case EventType::KeyType:
      ProcessKeyTypeEvent(std::static_pointer_cast<KeyTypeEvent>(event));
      break;

    case EventType::MouseButtonPress:
    case EventType::MouseButtonRelease:
      ProcessMouseButtonEvent(std::static_pointer_cast<MouseButtonEvent>(event));
      break;

    case EventType::MouseMove:
      ProcessMouseMoveEvent(std::static_pointer_cast<MouseMoveEvent>(event));
      break;

    case EventType::MouseScroll:
      ProcessMouseScrollEvent(std::static_pointer_cast<MouseScrollEvent>(event));
      break;

    default:
      LOG_DEBUG("Debug layer dropped unhandled event [{}]", event->Log());
      break;
  }
}

void Squirrel::DebugLayer::ProcessWindowFocusEvent(const std::shared_ptr<WindowFocusEvent> window_focus_event)
{
  ImGuiIO& io = ImGui::GetIO();
  io.AddFocusEvent(EventType::WindowFocus == window_focus_event->GetEventType());
}

void Squirrel::DebugLayer::ProcessMouseButtonEvent(const std::shared_ptr<MouseButtonEvent> mouse_button_event)
{
  ImGuiIO& io = ImGui::GetIO();
  io.AddMouseButtonEvent(mouse_button_event->GetButton(),
                         (EventType::MouseButtonPress == mouse_button_event->GetEventType()));
}

void Squirrel::DebugLayer::ProcessMouseMoveEvent(const std::shared_ptr<MouseMoveEvent> mouse_move_event)
{
  ImGuiIO& io = ImGui::GetIO();
  io.AddMousePosEvent(mouse_move_event->GetPositionX(), mouse_move_event->GetPositionY());
}

void Squirrel::DebugLayer::ProcessMouseScrollEvent(const std::shared_ptr<MouseScrollEvent> mouse_scroll_event)
{
  ImGuiIO& io = ImGui::GetIO();
  io.AddMouseWheelEvent(mouse_scroll_event->GetOffsetX(), mouse_scroll_event->GetOffsetY());
}

void Squirrel::DebugLayer::ProcessKeyPressEvent(const std::shared_ptr<KeyPressEvent> key_press_event)
{
  ImGuiIO& io        = ImGui::GetIO();
  ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(key_press_event->GetKey(), key_press_event->GetScanCode());
  if (imgui_key == ImGuiKey_None)
  {
    CONSOLE_ERROR("Unknown Key keyevent [{}]", key_press_event->Log());
    return;
  }
  io.AddKeyEvent(imgui_key, (key_press_event->GetEventType() != EventType::KeyRelease));
  io.AddKeyEvent(ImGuiKey_ModCtrl, (key_press_event->GetMods() & GLFW_MOD_CONTROL) != 0);
  io.AddKeyEvent(ImGuiKey_ModShift, (key_press_event->GetMods() & GLFW_MOD_SHIFT) != 0);
  io.AddKeyEvent(ImGuiKey_ModAlt, (key_press_event->GetMods() & GLFW_MOD_ALT) != 0);
  io.AddKeyEvent(ImGuiKey_ModSuper, (key_press_event->GetMods() & GLFW_MOD_SUPER) != 0);
}

void Squirrel::DebugLayer::ProcessKeyTypeEvent(const std::shared_ptr<KeyTypeEvent> key_type_event)
{
  ImGuiIO& io = ImGui::GetIO();
  io.AddInputCharacter(key_type_event->GetCodePoint());
}
