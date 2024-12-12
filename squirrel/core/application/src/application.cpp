#include "application.h"
#include "log-impl.h"

#include "event_manager.h"

#include <unistd.h> // For timed loop, remove when not needed

namespace Squirrel
{

Application::Application(){};
Application::~Application(){};

void Application::Init()
{
  ::Utils::Logger::Init();

  event_manager_ = std::make_unique<EventManager>();
  event_manager_->Init();
  is_running = true;
  CONSOLE_INFO("Initialised Squirrel Engine successfully");
}

void Application::DeInit()
{
  CONSOLE_INFO("DeInitialising Squirrel Engine");

  event_manager_->DeInit();
  ::Utils::Logger::DeInit();
  is_running = false;
}

void Application::Run()
{
  CONSOLE_INFO("Booting up the Squirrel Engine!");
  while (is_running && event_manager_->IsRunning())
  {
    event_manager_->DispatchEvents();
  }
}
} // namespace Squirrel
