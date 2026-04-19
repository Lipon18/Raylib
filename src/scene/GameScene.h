#pragma once

#include "Scene.h"
#include "character/AssetData.h"
#include <memory>

class GameLevel;
class SceneManager;

class GameScene : public Scene {
public:
    GameScene(SceneManager* mgr);
    ~GameScene();

    void OnEnter() override;
    void Update(float dt) override;
    void Draw() override;

private:
    GameLevel* m_Level = nullptr;
    GameAssets m_Assets;
    SceneManager* m_Manager;
};