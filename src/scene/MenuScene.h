#pragma once
#include "Scene.h"
#include "gameplay/MainMenu.h"

class SceneManager;

class MenuScene : public Scene {
public:
    MenuScene(SceneManager* mgr);

    //void OnEnter() override;
    void Update(float dt) override;
    void Draw() override;

private:
    MainMenu m_Menu;
    SceneManager* m_Manager;
};