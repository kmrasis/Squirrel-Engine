#include "debug_layer.h"
#include "imgui_impl_glfw.cpp"
#include "imgui_impl_opengl3.h"

#include "log-impl.h"

Squirrel::DebugLayer::DebugLayer()
    : Layer("DebugLayer"){};
Squirrel::DebugLayer::~DebugLayer() = default;

void Squirrel::DebugLayer::Attach()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  ImGuiIO& io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  ImGui_ImplOpenGL3_Init("#version 410");
}

void Squirrel::DebugLayer::Detach() {}
void Squirrel::DebugLayer::Update()
{
  ImGuiIO& io    = ImGui::GetIO();
  io.DisplaySize = ImVec2(600, 800);
  io.DeltaTime   = 1.0f / 60.0f;

  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  static bool show = true;
  ImGui::ShowDemoWindow(&show);
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void Squirrel::DebugLayer::HandleEvent(const std::shared_ptr<Event> event)
{
  LOG_TRACE("SQUIRREL :: Recieved event in layer : {}. EVENT DATA: [{}]", debug_name_, event->Log());
}
