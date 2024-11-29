#include "application.h"
#include "log.hpp"

namespace Squirrel {
    Application::Application() {};

    Application::~Application() {};

    void Application::run() {
            std::cout << "Starting Application!" << std::endl;
            
            ::Log::Logger::Init();

            CONSOLE_INFO("Hi! This is an example warn log from core logger");
            CONSOLE_WARN("Hi! This is an example warn log from core logger");
            CONSOLE_ERROR("Hi! This is an example warn log from core logger");
            
            LOG_TRACE("Hi! This is an example error log from console");
            LOG_DEBUG("Hi! This is an example error log from console");
            LOG_INFO("Hi! This is an example error log from console");
            LOG_WARN("Hi! This is an example error log from console");
            LOG_ERROR("Hi! This is an example error log from console");
            
            while (true) {}
    }
}