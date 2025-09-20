#pragma once

#include <memory>
#include <string>

namespace Squirrel
{
class Event;
class OrthoCamera;
class Layer
{
public:
  Layer(const std::string& debug_name = "Layer");
  virtual ~Layer();
  virtual void Attach();
  virtual void Detach();
  virtual void Update(const float& delta_time_s);
  virtual void Render();
  virtual void ImGuiRender();
  virtual void HandleEvent(const std::shared_ptr<Event> event);
  inline const std::string& GetName() const { return debug_name_; };

  void SetCamera(OrthoCamera* camera);

protected:
  std::string debug_name_;
  OrthoCamera* camera_;
};
} // namespace Squirrel
