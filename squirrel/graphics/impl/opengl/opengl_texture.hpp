#include "log-impl.h"
#include "texture.h"

#include <glad/glad.h>
#include <stb/image.h>

namespace Squirrel::GFX::OpenGL
{
class OpenGLTexture2D : public Texture2D
{
public:
  OpenGLTexture2D(const char* path)
  {
    int w = 0, h = 0, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(path, &w, &h, &channels, 0);
    if (!data)
    {
      CONSOLE_ERROR("Failed to load image!: [{}]", path);
      return;
    }
    width_  = w;
    height_ = h;

    GLenum internalFormat, externalFormat;
    switch (channels)
    {
      case 1:
        internalFormat = GL_R8;
        externalFormat = GL_RED;
        break;

      case 2:
        internalFormat = GL_RG8;
        externalFormat = GL_RG;
        break;

      case 3:
        internalFormat = GL_RGB8;
        externalFormat = GL_RGB;
        break;

      case 4:
        internalFormat = GL_RGBA8;
        externalFormat = GL_RGBA;
        break;

      default:
        internalFormat = GL_RGB8;
        externalFormat = GL_RGB;
        break;
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &texture_id_);
    glTextureStorage2D(texture_id_, 1, internalFormat, width_, height_);

    glTextureParameteri(texture_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(texture_id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTextureSubImage2D(texture_id_, 0, 0, 0, width_, height_, externalFormat, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
  }
  ~OpenGLTexture2D() { glDeleteTextures(1, &texture_id_); }

  void Bind(uint32_t slot = 0) const override { glBindTextureUnit(slot, texture_id_); }

private:
  GLuint texture_id_;
};
} // namespace Squirrel::GFX::OpenGL
