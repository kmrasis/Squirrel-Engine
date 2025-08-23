#include "debug_layer.h"
#include "event.h"
#include "imgui_impl_glfw.cpp"
#include "imgui_impl_opengl3.h"

#include "log-impl.h"

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
  LOG_TRACE("SQUIRREL :: Recieved event in layer : {}. EVENT DATA: [{}]", debug_name_, event->Log());
}
