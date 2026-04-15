#pragma once

#include "window/GWindow.h"

class Application {
    public:
    Application();

    void Run();

    private:
    GWindow m_Window;

    void Update();
    void Draw();
};