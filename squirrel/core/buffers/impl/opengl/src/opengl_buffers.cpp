#include "opengl_buffers.h"

#include "glad/glad.h"

namespace Squirrel
{

// OpenGL Vertex Buffer Impl
OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int count)
{
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), (GLfloat*)vertices, GL_STATIC_DRAW);
}
OpenGLVertexBuffer::~OpenGLVertexBuffer() = default;

void OpenGLVertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, VBO); }
void OpenGLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

// OpenGL Index Buffer Impl
OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count)
{
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), (GLuint*)indices, GL_STATIC_DRAW);
}
OpenGLIndexBuffer::~OpenGLIndexBuffer() = default;
void OpenGLIndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); }
void OpenGLIndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
} // namespace Squirrel
