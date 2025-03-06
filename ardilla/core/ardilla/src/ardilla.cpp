#include "ardilla.h"
#include "layer_example.h"

Ardilla::Ardilla()
    : Application()
{
  Init();
  PushLayer(new ExampleLayer());
}
Ardilla::~Ardilla() = default;

Squirrel::Application* Squirrel::CreateApplication() { return new Ardilla(); }
