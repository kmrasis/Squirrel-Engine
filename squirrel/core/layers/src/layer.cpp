#include "layer.h"
#include <memory>

namespace Squirrel
{
Layer::Layer(const std::string& debug_name) { debug_name_ = debug_name; }
Layer::~Layer() = default;

void Layer::Attach() {}
void Layer::Detach() {}
void Layer::Update() {}
void Layer::Render() {}
void Layer::ImGuiRender() {}
void Layer::HandleEvent(const std::shared_ptr<Event> event) {}
void Layer::SetCamera(OrthoCamera* camera) { camera_ = camera; }
} // namespace Squirrel
