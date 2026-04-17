#pragma once

#include "window/GWindow.h"
#include <memory>
#include <vector>
#include "utilities/TextureManager.h"
#include "character/AssetData.h"

class GCamera;
class World;
class Player;
class Zombie;
class AssetManager;
class Spawner;

class Application {
    public:
    Application();
    ~Application();

    void Run();

    private:
    GWindow m_Window;

    void Update();
    void Draw();

    std::unique_ptr<AssetManager> m_Asset;
    std::unique_ptr<World> m_World;
    std::unique_ptr<GCamera> m_Camera;
    std::unique_ptr<Player> m_Player;
    std::vector<std::unique_ptr<Zombie>> m_Zombies;
    std::unique_ptr<Spawner> m_Spawner;

    GameAssets m_GameAssets;

    Vector2 m_TestPoint = {1000, 1000};
};