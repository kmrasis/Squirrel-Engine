#include "application.h"
#include "log.hpp"
#include "appEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"
#include "windowEvent.h"

namespace Squirrel {

    Application::Application() {};
    
    Application::~Application() {};

    void Application::run() {
        ::Log::Logger::Init();
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
        LOG_TRACE("Hi! This is an example error log from console");
        LOG_DEBUG("Hi! This is an example error log from console");
        LOG_INFO("Hi! This is an example error log from console");
        LOG_WARN("Hi! This is an example error log from console");
        LOG_ERROR("Hi! This is an example error log from console");
    #endif
        while (true) {}
    }
} //namespace Squirrel
