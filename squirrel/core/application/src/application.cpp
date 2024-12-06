#include "application.h"
#include "log-impl.h"

#include "appEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"
#include "windowEvent.h"

#include "window_manager.h"
#include "window_property.h"

#include <unistd.h> // For timed loop, remove when not needed

namespace Squirrel
{

Application::Application(){};
Application::~Application(){};

void Application::Init()
{
  ::Utils::Logger::Init();

  window_manager_ = std::make_unique<WindowManager>();
  window_manager_->Init();

  CONSOLE_INFO("Initialised Squirrel Engine successfully");
}

void Application::DeInit()
{
  CONSOLE_INFO("DeInitialising Squirrel Engine");

  window_manager_->DeInit();

  ::Utils::Logger::DeInit();
}

void Application::Run()
{
  CONSOLE_INFO("Booting up the Squirrel Engine!");

  MouseEvent mouseEvent(EventType::MouseMove, 10, 20, 0, 0, 1, 1);
  CONSOLE_INFO(mouseEvent.Log());

  WindowProperty props;
  window_manager_->CreateWindow(props);
  sleep(15);
  window_manager_->CloseWindow();

  while (is_running)
  {}
}
} // namespace Squirrel
