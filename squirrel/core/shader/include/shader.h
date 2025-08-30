namespace Squirrel
{
class Shader
{
protected:
  Shader();

public:
  static Shader* CreateShader(const char* vertex_src, const char* fragment_src);
  virtual ~Shader();

  virtual void Bind() const   = 0;
  virtual void Unbind() const = 0;
};
} // namespace Squirrel
