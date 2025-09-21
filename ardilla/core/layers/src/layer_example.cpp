#include "layer_example.h"
#include "log-impl.h"

#include "event.h"
#include "graphics.h"
#include "input_poller.h"

#include "camera.h"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

namespace Layer::Example
{
// Vertex Shader source
const char* vertex_src = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexture;

out vec2 vTexture;

uniform mat4 viewProjectionMatrix;
uniform mat4 transform;

void main()
{
    gl_Position = viewProjectionMatrix * transform * vec4(aPosition, 1.0);
    vTexture = aTexture;
}
)glsl";

// Fragment Shader source
const char* fragment_src = R"glsl(
#version 330 core
in vec2 vTexture;
out vec4 FragColor;

uniform sampler2D Texture2d;

void main()
{
    FragColor = texture(Texture2d, vTexture);
}
)glsl";

glm::vec3 scale_v(1.0f);
glm::vec3 pos(0.0f);
float del = 1.0f;

Squirrel::GFX::Shader* shader;
const char* honeycomb_texture_path
    = "/home/thespace/Desktop/Projects/Squirrel-Engine/ardilla/core/assets/textures/honeycomb.png";
Squirrel::GFX::Texture2D* texture;
int texture_slot = 0;
} // namespace Layer::Example
using namespace Layer::Example;

ExampleLayer::ExampleLayer()
    : Layer("Example"){};
ExampleLayer ::~ExampleLayer() = default;

void ExampleLayer::Attach()
{
  float vertices[] = {
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // 0
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // 1
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // 2
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f  // 3
  };

  int indices[] = {
    0, 1, 2, // 0
    2, 3, 0  // 1
  };

  shader    = Squirrel::GFX::Device::CreateShader(vertex_src, fragment_src);
  pipeline_ = Squirrel::GFX::Device::CreatePipeline(shader);
  texture   = Squirrel::GFX::Device::CreateTexture2D(honeycomb_texture_path);

  shader->Bind();
  shader->UploadUniformInt("Texture2d", texture_slot);

  auto vtx_buffer = Squirrel::GFX::Device::CreateBuffer(
      Squirrel::GFX::BufferType::Vertex, Squirrel::GFX::BufferUsage::Static, &vertices, sizeof(vertices));
  auto idx_buffer = Squirrel::GFX::Device::CreateBuffer(
      Squirrel::GFX::BufferType::Index, Squirrel::GFX::BufferUsage::Static, &indices, sizeof(indices));
  Squirrel::GFX::VertexLayout vtx_layout = Squirrel::GFX::VertexLayout(5);
  vtx_layout.AddAttribute(0, 0, 3);
  vtx_layout.AddAttribute(1, 3, 2);

  mesh_ = Squirrel::GFX::Device::CreateMesh(vtx_buffer, vtx_layout, 4, idx_buffer, 2);
}
void ExampleLayer::Detach()
{
  delete mesh_;
  delete texture;
  delete shader;
  delete pipeline_;
}
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
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), scale_v);
  shader->UploadUniformMat4("viewProjectionMatrix", camera_->GetViewProjectionMatrix());
  shader->UploadUniformMat4("transform", transform);
  texture->Bind(texture_slot);
  mesh_->Draw();
  pipeline_->Unbind();
}

void ExampleLayer::ImGuiRender()
{
  if (!ImGui::Begin("Square controls"))
  {
    ImGui::End();
    return;
  }
  ImGui::DragFloat("Speed", &del, 0.1f, 0.0f, 5.0f, "%.2f");
  ImGui::DragFloat2("Scale", glm::value_ptr(scale_v), 0.1f, 0.0f, 2.0f, "%.2f");
  ImGui::DragFloat2("Pos", glm::value_ptr(pos), 0.1f, -1.0f, 1.0f, "%.2f");

  ImGui::End();
}

void ExampleLayer::HandleEvent(const std::shared_ptr<Squirrel::Event> event)
{
  LOG_TRACE("ARDILLA :: Received event in  layer : {}. EVENT DATA: [{}]", debug_name_, event->Log());
}
