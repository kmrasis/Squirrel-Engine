#include "squirrel.h"

class Ardilla : public Squirrel::Application {
    public:
        Ardilla() = default;
        ~Ardilla() = default;
};

Squirrel::Application* Squirrel::CreateApplication() {
    return new Ardilla();
}
