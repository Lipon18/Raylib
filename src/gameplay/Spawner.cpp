#include "Spawner.h"
#include "character/Player.h"
#include "character/Zombie.h"
#include "character/AssetData.h"
#include "gameplay/sound/SoundManager.h"
#include "raymath.h"

Spawner::Spawner(Player* player, const GameAssets& assets, SoundManager* soundMgr) : m_TargetPlayer(player), m_Assets(assets), m_SoundManager(soundMgr) {}

void Spawner::Update(float dt, std::vector<std::unique_ptr<Zombie>>& zombies) {
    if(!m_TargetPlayer) return;

    m_SpawnTimer += dt;
    if (m_SpawnTimer >= m_SpawnInterval) {
        Spawn(zombies);
        m_SpawnTimer = 0.0f;
    }
}

void Spawner::Spawn(std::vector<std::unique_ptr<Zombie>>& zombies) {
    if (!m_TargetPlayer) return;

    float angle = (float)GetRandomValue(0, 360) * DEG2RAD;
    float distance = (float)GetRandomValue((int)m_MinSpawnDist, (int)m_MaxSpawnDist);
    Vector2 offset = { cosf(angle) * distance, sinf(angle) * distance };
    Vector2 spawnPos = Vector2Add(m_TargetPlayer->GetPosition(), offset);
    auto zombie = std::make_unique<Zombie>(spawnPos, m_TargetPlayer, m_Assets, m_SoundManager);
    zombies.push_back(std::move(zombie));
}