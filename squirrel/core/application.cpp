#include "application.h"
#include <iostream>

namespace Squirrel {
    Application::Application() {};

    Application::~Application() {};

    void Application::run() {
            std::cout << "Starting Application!" << std::endl;
            while (true) {}
    }
}