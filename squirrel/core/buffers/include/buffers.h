namespace Squirrel
{
class VertexBuffer
{
protected:
  VertexBuffer();

public:
  virtual ~VertexBuffer();
  virtual void Bind() const   = 0;
  virtual void Unbind() const = 0;
  static VertexBuffer* CreateVertexBuffer(float* vertices, unsigned int count);
};

class IndexBuffer
{
protected:
  IndexBuffer();

public:
  virtual ~IndexBuffer();
  virtual void Bind() const   = 0;
  virtual void Unbind() const = 0;
  static IndexBuffer* CreateIndexBuffer(unsigned int* indices, unsigned int count);
};
} // namespace Squirrel
