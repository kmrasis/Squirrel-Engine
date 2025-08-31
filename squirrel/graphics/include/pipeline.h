#pragma once

namespace Squirrel::GFX
{
class Pipeline
{
public:
  virtual ~Pipeline()         = default;
  virtual void Bind() const   = 0;
  virtual void Unbind() const = 0;
};
} // namespace Squirrel::GFX
