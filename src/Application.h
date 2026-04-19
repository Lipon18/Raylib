#pragma once

#include "window/GWindow.h"
#include <memory>
#include <vector>
#include "utilities/TextureManager.h"
#include "character/AssetData.h"

class MainMenu;
class GameLevel;
class AssetManager;

enum class AppState {
    Menu,
    Playing
};

class Application {
    public:
    Application();
    ~Application();

    void Run();
    void Update();
    void Draw();

    private:
    GWindow m_Window;

    AppState m_State;
    std::unique_ptr<MainMenu> m_Menu;
    std::unique_ptr<GameLevel> m_GameLevel;
    std::unique_ptr<AssetManager> m_Asset;
};