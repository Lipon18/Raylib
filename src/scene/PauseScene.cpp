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
    int w = GetScreenWidth();
    int h = GetScreenHeight();

    DrawRectangle(0, 0, w, h, Color{0, 0, 0, 160});
    const char* text = "PAUSED";
    int fontSize = 40;
    int textWidth = MeasureText(text, fontSize);

    DrawText(text, (w - textWidth) / 2, (h - fontSize) / 2, fontSize, WHITE);

    const char* hint = "Press P to resume";
    int hintWidth = MeasureText(hint, 20);

    DrawText(hint, (w - hintWidth) / 2, (h / 2) + 40, 20, YELLOW);
}