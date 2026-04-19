#include "PauseScene.h"
#include "SceneManager.h"
#include "MenuScene.h"

PauseScene::PauseScene(SceneManager* mgr) : m_Manager(mgr) {}

void PauseScene::Update(float dt) {
     if (IsKeyPressed(KEY_P))
        m_Manager->Request(SceneType::Game);

    if (IsKeyPressed(KEY_ESCAPE))
        m_Manager->Request(SceneType::Menu);
}

void PauseScene::Draw() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 160});
    DrawText("PAUSED", 350, 200, 40, WHITE);;
}