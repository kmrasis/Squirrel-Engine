#include "layer_example.h"
#include "log-impl.h"

#include "event.h"
#include "input_poller.h"

#include "imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 position(0.0f, 0.0f, 0.0f);
glm::vec3 rotation(0.0f, 0.0f, 0.0f);
glm::vec3 scale(1.0f, 1.0f, 1.0f);

ExampleLayer::ExampleLayer()
    : Layer("Example"){};
ExampleLayer ::~ExampleLayer() = default;

void ExampleLayer::Attach() {}
void ExampleLayer::Detach() {}
void ExampleLayer::Update()
{
  Squirrel::InputPoller& ip = Squirrel::InputPoller::GetInputPoller();
  LOG_INFO("Is 'A' Key pressed [{}]", ip.IsKeyPressed('A'));
  LOG_INFO("Mouse at: [{}, {}]", ip.GetCursorX(), ip.GetCursorY());
}

void ExampleLayer::Render() {}

void ExampleLayer::ImGuiRender()
{
  if (!ImGui::Begin("Example Transform Controls"))
  {
    ImGui::End();
    return;
  }

  // Editable controls
  ImGui::DragFloat3("Position", glm::value_ptr(position), 0.1f);
  ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.1f);
  ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f);

  // Build transform matrix with GLM
  glm::mat4 model = glm::mat4(1.0f);
  model           = glm::translate(model, position);
  model           = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
  model           = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
  model           = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
  model           = glm::scale(model, scale);

  // Show Matrix
  ImGui::Text("Model Matrix");
  for (int i = 0; i < 4; ++i)
  {
    ImGui::Text("[%.2f %.2f %.2f %.2f]", model[i][0], model[i][1], model[i][2], model[i][3]);
  }
  ImGui::End();
}

void ExampleLayer::HandleEvent(const std::shared_ptr<Squirrel::Event> event)
{
  LOG_TRACE("ARDILLA :: Received event in  layer : {}. EVENT DATA: [{}]", debug_name_, event->Log());
}
