#include "layer_example.h"

#include "event.h"

#include "log-impl.h"

ExampleLayer::ExampleLayer()
    : Layer("Example"){};
ExampleLayer ::~ExampleLayer() = default;

void ExampleLayer::Attach() {}
void ExampleLayer::Detach() {}
void ExampleLayer::Update() {}
void ExampleLayer::HandleEvent(const std::shared_ptr<Squirrel::Event> event)
{
  LOG_TRACE("ARDILLA :: Received event in  layer : {}. EVENT DATA: [{}]", debug_name_, event->Log());
}
