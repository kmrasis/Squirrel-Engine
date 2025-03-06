#pragma once

#include <memory>
#include <string>

namespace Squirrel
{
class Event;
class Layer
{
public:
  Layer(const std::string& debug_name = "Layer");
  virtual ~Layer();
  virtual void Attach();
  virtual void Detach();
  virtual void Update();
  virtual void HandleEvent(const std::shared_ptr<Event> event);
  inline const std::string& GetName() const { return debug_name_; };

protected:
  std::string debug_name_;
};
} // namespace Squirrel
