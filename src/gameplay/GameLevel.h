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
class SoundManager;
struct GameAssets;

class GameLevel {
    public:
    GameLevel(const GameAssets& assets);
    ~GameLevel();

    void Update(float dt);
    void Draw();

    bool IsGameOver() const {return m_GameOver;}
    int GetFinalScore() const { return m_FinalScore; }

    private:
    const GameAssets& m_Assets;

    std::unique_ptr<Player> m_Player;
    std::vector<std::unique_ptr<Zombie>> m_Zombies;
    std::unique_ptr<Spawner> m_Spawner;
    std::unique_ptr<GameMode> m_GameMode;
    std::unique_ptr<World> m_World;
    std::unique_ptr<GCamera> m_Camera;
    std::unique_ptr<SoundManager> m_SoundManager;

    bool m_GameOver = false;
    int m_FinalScore = 0;

    void GameOver();
};