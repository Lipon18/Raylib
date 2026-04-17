#pragma once 

#include "raylib.h"
#include <vector>
#include <memory>

class Player;
class Zombie;
struct GameAssets;

class Spawner {
    public:
    Spawner(Player* player, const GameAssets& assets);

    void Update(float dt, std::vector<std::unique_ptr<Zombie>>& zombies);

    private:
    void Spawn(std::vector<std::unique_ptr<Zombie>>& zombies);

    Player* m_TargetPlayer;
    const GameAssets& m_Assets;

    float m_SpawnTimer = 0.0f;
    float m_SpawnInterval = 2.0f;
    float m_MinSpawnDist = 500.0f;
    float m_MaxSpawnDist = 800.0f;
};