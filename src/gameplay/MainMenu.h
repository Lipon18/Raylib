#pragma once

#include "raylib.h"

enum class MenuAction {
    None,
    Start,
    Quit
};

class MainMenu {
    public:
    bool ShouldStartGame() const;
    bool ShouldQuitGame() const;
    void Draw();
    MenuAction Update();

    private:
    Rectangle m_PlayButton = { 0, 0, 200, 60 };
    Rectangle m_QuitButton = { 0, 0, 200, 60 };
};