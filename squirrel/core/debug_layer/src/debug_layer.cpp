#include "debug_layer.h"
#include "log-impl.h"

#include "glad/glad.h"
#include "shader.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "appEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"
#include "windowEvent.h"

Squirrel::DebugLayer::DebugLayer()
    : Layer("DebugLayer"){};
Squirrel::DebugLayer::~DebugLayer() = default;

ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int keycode, int scancode);
std::shared_ptr<Squirrel::Shader> Squirrel::DebugLayer::shader_ = nullptr;
void Squirrel::DebugLayer::Init(void* window)
{
  window_ = (GLFWwindow*)window;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  ImGuiIO& io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
  // io.ConfigViewportsNoAutoMerge = true;
  // io.ConfigViewportsNoTaskBarIcon = true;

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGuiStyle& style                 = ImGui::GetStyle();
    style.WindowRounding              = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

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
  if (shader_)
  {
    shader_.reset();
  }
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

void Squirrel::DebugLayer::Render()
{
  static GLfloat vertices[] = {
      // pos              // color
      -0.2f, 0.7f,  0.0f, 0.2f, 0.7f, 0.0f, // 0
      0.2f,  0.7f,  0.0f, 0.6f, 0.7f, 0.0f, // 1
      -0.1f, 0.6f,  0.0f, 0.3f, 0.6f, 0.0f, // 2
      0.1f,  0.6f,  0.0f, 0.5f, 0.6f, 0.0f, // 3
      -0.1f, 0.2f,  0.0f, 0.3f, 0.2f, 0.0f, // 4
      0.1f,  0.2f,  0.0f, 0.5f, 0.2f, 0.0f, // 5
      -0.1f, 0.1f,  0.0f, 0.3f, 0.1f, 0.0f, // 6
      0.2f,  0.1f,  0.0f, 0.5f, 0.1f, 0.0f, // 7
      -0.2f, -0.7f, 0.0f, 0.2f, 0.7f, 0.0f, // 8
      -0.1f, -0.7f, 0.0f, 0.3f, 0.7f, 0.0f, // 9
  };
  static GLuint indices[] = {
      0, 2, 8, // 0
      2, 8, 9, // 1
      0, 1, 2, // 2
      1, 2, 3, // 3
      1, 3, 7, // 4
      3, 7, 5, // 5
      7, 5, 6, // 6
      5, 6, 4  // 7
  };
  static GLuint VAO, VBO, EBO;
  shader_ = Shader::CreateShader(nullptr, nullptr);

  static bool first_call = true;
  if (first_call)
  {
    first_call = false;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 60 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    // Set Attributes for vertex/color attributes
    // (Attribute pos) (3 Data points: x,y,z for each) (stride)(offset/pos of 1st element)

    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
  shader_->Bind();
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (void*)0);
}
void Squirrel::DebugLayer::ImGuiRender()
{
  LOG_DEBUG("Show demo ImGUI Window");
  ImGui::ShowDemoWindow();
}
void Squirrel::DebugLayer::DrawFrame()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Update and Render additional Platform Windows
  // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this
  // code elsewhere.
  //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    // Known Issue: Multiviewport doesnt work nicely with linux causing unexpected behaviour
    // when dragging window to the edge of display
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(window_);
  }
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
