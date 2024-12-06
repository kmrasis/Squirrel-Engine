#include "ardilla.h"

Ardilla::Ardilla()  = default;
Ardilla::~Ardilla() = default;

Squirrel::Application* Squirrel::CreateApplication() { return new Ardilla(); }
