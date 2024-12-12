#include <string>

namespace Squirrel
{
class WindowProperty
{
public:
  std::string Title = "Squirrel Engine";
  bool Focus        = true;
  int PosX          = 0;
  int PosY          = 0;
  int Height        = 720;
  int Width         = 1280;
};
} // namespace Squirrel
