#pragma once
#include "Scene.h"
#include "raylib.h"

class SceneManager;

class PauseScene : public Scene {
public:
    PauseScene(SceneManager* mgr);

    void Update(float dt) override;
    void Draw() override;

private:
    SceneManager* m_Manager;
};