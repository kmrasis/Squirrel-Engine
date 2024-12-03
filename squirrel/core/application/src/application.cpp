#include "application.h"
#include "log-impl.h"
#include "appEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"
#include "windowEvent.h"

namespace Squirrel
{

    Application::Application() {};
    Application::~Application() {};

    void Application::Init()
    {
        ::Utils::Logger::Init();
        CONSOLE_INFO("Initialised Squirrel Engine successfully");
    }

    void Application::DeInit()
    {
        CONSOLE_INFO("DeInitialising Squirrel Engine");
        ::Utils::Logger::DeInit();
    }

    void Application::Run()
    {
        CONSOLE_INFO("Booting up the Squirrel Engine!");

        ApplicationEvent appEvent(EventType::AppUpdate);
        CONSOLE_INFO(appEvent.Log());

        KeyboardEvent keyEvent(EventType::KeyPress, 10, 1);
        CONSOLE_INFO(keyEvent.Log());

        MouseEvent mouseEvent(EventType::MouseMove, 10, 20, 0, 0, 1, 1);
        CONSOLE_INFO(mouseEvent.Log());

        WindowEvent windowEvent(EventType::WindowMove, 10, 20);
        CONSOLE_INFO(windowEvent.Log());

#ifdef SQ_ENABLE_TRACE_LOGGING
        CONSOLE_INFO("Hi! This is an example info log from console");
        CONSOLE_WARN("Hi! This is an example warn log from console");
        CONSOLE_ERROR("Hi! This is an example error log from console");

        LOG_TRACE("Hi! This is an example trace log from core");
        LOG_DEBUG("Hi! This is an example debug log from core");
        LOG_INFO("Hi! This is an example info log from core");
        LOG_WARN("Hi! This is an example warn log from core");
        LOG_ERROR("Hi! This is an example error log from core");
#endif
        while (is_running)
        {
        }
    }
} // namespace Squirrel
