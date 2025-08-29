namespace Squirrel
{
class GraphicsContext
{
protected:
  GraphicsContext();

public:
  virtual ~GraphicsContext();
  virtual void StartNewFrame(const int& width, const int& height) = 0;
  static GraphicsContext* CreateGraphicsContext();
};
} // namespace Squirrel
