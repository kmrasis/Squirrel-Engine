#pragma once

namespace Squirrel
{

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Init();
        void DeInit();

        void Run();

    private:
        bool is_running = false;
    };

    // To be defined in client
    Application *CreateApplication();
}
