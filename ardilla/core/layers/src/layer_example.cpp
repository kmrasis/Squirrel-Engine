#include "layer_example.h"
#include "log-impl.h"

#include "event.h"
#include "graphics.h"
#include "input_poller.h"

#include "imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
    : Layer("Example"){};
ExampleLayer ::~ExampleLayer() = default;

void ExampleLayer::Attach() { pipeline_ = Squirrel::GFX::Device::CreatePipeline(nullptr); }
void ExampleLayer::Detach() {}
void ExampleLayer::Update()
{
  Squirrel::InputPoller& ip = Squirrel::InputPoller::GetInputPoller();

  int up    = ip.IsKeyPressed('W') ? 1 : 0;
  int down  = ip.IsKeyPressed('S') ? 1 : 0;
  int left  = ip.IsKeyPressed('A') ? 1 : 0;
  int right = ip.IsKeyPressed('D') ? 1 : 0;

  float xdel = del * (right - left);
  float ydel = del * (up - down);

  // shift x
  if (vertices[0] + xdel > -1.0f && vertices[6] + xdel < 1.0f)
  {
    vertices[0] += xdel;
    vertices[6] += xdel;
    vertices[12] += xdel;
    vertices[18] += xdel;
  }

  // shift y
  if (vertices[1] + ydel < 1.0f && vertices[19] + ydel > -1.0f)
  {
    vertices[1] += ydel;
    vertices[7] += ydel;
    vertices[13] += ydel;
    vertices[19] += ydel;
  }
  auto vtx_buffer = Squirrel::GFX::Device::CreateBuffer(
      Squirrel::GFX::BufferType::Vertex, Squirrel::GFX::BufferUsage::Static, &vertices, sizeof(vertices));
  auto idx_buffer = Squirrel::GFX::Device::CreateBuffer(
      Squirrel::GFX::BufferType::Index, Squirrel::GFX::BufferUsage::Static, &indices, sizeof(indices));
  Squirrel::GFX::VertexLayout vtx_layout = Squirrel::GFX::VertexLayout(6);
  vtx_layout.AddAttribute(0, 0, 3);
  vtx_layout.AddAttribute(1, 3, 3);

  mesh_ = Squirrel::GFX::Device::CreateMesh(vtx_buffer, vtx_layout, 4, idx_buffer, 2);
}

void ExampleLayer::Render()
{
  pipeline_->Bind();
  mesh_->Draw();
  pipeline_->Unbind();
}

void ExampleLayer::ImGuiRender()
{
  if (!ImGui::Begin("Example Transform Controls"))
  {
    ImGui::End();
    return;
  }
  glm::vec2 position1(vertices[0], vertices[1]);
  glm::vec2 position2(vertices[6], vertices[7]);
  glm::vec2 position3(vertices[12], vertices[13]);
  glm::vec2 position4(vertices[18], vertices[19]);
  // Editable controls
  ImGui::DragFloat2("Pos1", glm::value_ptr(position1), 0.1f);
  ImGui::DragFloat2("Pos2", glm::value_ptr(position2), 0.1f);
  ImGui::DragFloat2("Pos3", glm::value_ptr(position3), 0.1f);
  ImGui::DragFloat2("Pos4", glm::value_ptr(position4), 0.1f);
  ImGui::End();
}

void ExampleLayer::HandleEvent(const std::shared_ptr<Squirrel::Event> event)
{
  LOG_TRACE("ARDILLA :: Received event in  layer : {}. EVENT DATA: [{}]", debug_name_, event->Log());
}
