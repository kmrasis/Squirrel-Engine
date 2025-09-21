#pragma once

namespace Squirrel::GFX
{
class Texture
{
public:
  uint32_t GetWidth() { return width_; }
  uint32_t GetHeight() { return height_; }
  virtual void Bind(uint32_t slot = 0) const = 0;

protected:
  uint32_t width_;
  uint32_t height_;
};

class Texture2D : public Texture
{};
} // namespace Squirrel::GFX
