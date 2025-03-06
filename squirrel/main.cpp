#include <application.h>

extern Squirrel::Application* Squirrel::CreateApplication();

int main(int argc, char** argv)
{
  Squirrel::Application* app = Squirrel::CreateApplication();
  app->Run();
  app->DeInit();
  delete app;
}
