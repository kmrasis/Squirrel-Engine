#pragma once

namespace Squirrel {
    
    class Application {
    public:
        Application();

        virtual ~Application();

        void run();
    };

    // To be defined in client
    Application* CreateApplication();
}