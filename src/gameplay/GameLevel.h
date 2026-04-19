#pragma once

#include "raylib.h"
#include <memory>
#include <vector>

class Player;
class Zombie;
class Spawner;
class GameMode;
class World;
class GCamera;
struct GameAssets;

class GameLevel {
    public:
    GameLevel(const GameAssets& assets);
    ~GameLevel();

    void Update(float dt);
    void Draw();

    private:
    const GameAssets& m_Assets;

    std::unique_ptr<Player> m_Player;
    std::vector<std::unique_ptr<Zombie>> m_Zombies;
    std::unique_ptr<Spawner> m_Spawner;
    std::unique_ptr<GameMode> m_GameMode;
    std::unique_ptr<World> m_World;
    std::unique_ptr<GCamera> m_Camera;
};