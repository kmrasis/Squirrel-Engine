#include "layer_example.h"
#include "log-impl.h"

#include "event.h"
#include "graphics.h"
#include "input_poller.h"

#include "camera.h"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
    : Layer("Example"){};
ExampleLayer ::~ExampleLayer() = default;

glm::vec3 scale_v(0.2f);
glm::vec3 pos(0.0f);
float gap = 0.01f;

void ExampleLayer::Attach()
{
  pipeline_ = Squirrel::GFX::Device::CreatePipeline(nullptr);

  auto vtx_buffer = Squirrel::GFX::Device::CreateBuffer(
      Squirrel::GFX::BufferType::Vertex, Squirrel::GFX::BufferUsage::Static, &vertices, sizeof(vertices));
  auto idx_buffer = Squirrel::GFX::Device::CreateBuffer(
      Squirrel::GFX::BufferType::Index, Squirrel::GFX::BufferUsage::Static, &indices, sizeof(indices));
  Squirrel::GFX::VertexLayout vtx_layout = Squirrel::GFX::VertexLayout(6);
  vtx_layout.AddAttribute(0, 0, 3);
  vtx_layout.AddAttribute(1, 3, 3);

  mesh_ = Squirrel::GFX::Device::CreateMesh(vtx_buffer, vtx_layout, 4, idx_buffer, 2);
}
void ExampleLayer::Detach() { delete mesh_; }
void ExampleLayer::Update(const float& delta_time_s)
{
  Squirrel::InputPoller& ip = Squirrel::InputPoller::GetInputPoller();

#define KEY_UP 265
#define KEY_DOWN 264
#define KEY_LEFT 263
#define KEY_RIGHT 262

  int up    = ip.IsKeyPressed(KEY_UP) ? 1 : 0;
  int down  = ip.IsKeyPressed(KEY_DOWN) ? 1 : 0;
  int left  = ip.IsKeyPressed(KEY_LEFT) ? 1 : 0;
  int right = ip.IsKeyPressed(KEY_RIGHT) ? 1 : 0;

  float xdel = (del * (right - left)) * delta_time_s;
  float ydel = (del * (up - down)) * delta_time_s;

  // shift x
  pos.x += xdel;
  pos.y += ydel;

  // Camera Controls
  up    = ip.IsKeyPressed('W') ? 1 : 0;
  down  = ip.IsKeyPressed('S') ? 1 : 0;
  left  = ip.IsKeyPressed('A') ? 1 : 0;
  right = ip.IsKeyPressed('D') ? 1 : 0;

  int rotate_plus  = ip.IsKeyPressed('P') ? 1 : 0;
  int rotate_minus = ip.IsKeyPressed('O') ? 1 : 0;

  xdel = (del * (right - left)) * delta_time_s;
  ydel = (del * (up - down)) * delta_time_s;

  float rotate_del = (del * (rotate_plus - rotate_minus)) * delta_time_s;

  glm::vec3 camera_pos = camera_->GetPosition();
  camera_pos.x -= xdel;
  camera_pos.y -= ydel;
  camera_->SetPositionAndRotation(camera_pos, camera_->GetRotation() + rotate_del);
}

void ExampleLayer::Render()
{
  pipeline_->Bind();
  for (int x = 0; x < 3; ++x)
  {
    for (int y = 0; y < 3; ++y)
    {
      glm::mat4 transform
          = glm::translate(glm::mat4(1.0f),
                           glm::vec3(pos.x + x * (1.0f * scale_v.x + gap), pos.y + y * (1.0f * scale_v.y + gap), pos.z))
          * glm::scale(glm::mat4(1.0f), scale_v);
      pipeline_->GetShader()->UploadUniform("transform", transform);
      mesh_->Draw();
    }
  }
  pipeline_->Unbind();
}

void ExampleLayer::ImGuiRender()
{
  if (!ImGui::Begin("Variables"))
  {
    ImGui::End();
    return;
  }
  ImGui::DragFloat("Speed", &del, 0.1f, 0.0f, 5.0f, "%.2f");
  ImGui::DragFloat("Gap", &gap, 0.1f, 0.0f, 1.0f, "%.2f");
  ImGui::End();

  if (!ImGui::Begin("Scale_V"))
  {
    ImGui::End();
    return;
  }
  ImGui::DragFloat2("", glm::value_ptr(scale_v), 0.1f, 0.0f, 2.0f, "%.2f");
  ImGui::End();

  if (!ImGui::Begin("Pos_V"))
  {
    ImGui::End();
    return;
  }
  ImGui::DragFloat2("", glm::value_ptr(pos), 0.1f, -1.0f, 1.0f, "%.2f");
  ImGui::End();
}

void ExampleLayer::HandleEvent(const std::shared_ptr<Squirrel::Event> event)
{
  LOG_TRACE("ARDILLA :: Received event in  layer : {}. EVENT DATA: [{}]", debug_name_, event->Log());
}
