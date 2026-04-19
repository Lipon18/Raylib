#include "GameMode.h"
#include "character/Zombie.h"

GameMode::GameMode() {
    Init();
}

void GameMode::Init() {
    m_Score = 0;
}

void GameMode::Update(float dt) {}

void GameMode::OnZombieKilled(const Zombie* zombie) {
    m_Score += 10;
}