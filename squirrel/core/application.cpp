#include "application.h"
#include "log.hpp"

namespace Squirrel {

    Application::Application() {};
    
    Application::~Application() {};

    void Application::run() {
        ::Log::Logger::Init();
        CONSOLE_INFO("Booting up the Squirrel Engine!");
        CONSOLE_INFO("Hi! This is an example warn log from core logger");
        CONSOLE_WARN("Hi! This is an example warn log from core logger");
        CONSOLE_ERROR("Hi! This is an example warn log from core logger");

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
