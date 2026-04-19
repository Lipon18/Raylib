#include "MenuScene.h"
#include "SceneManager.h"
#include "utilities/AssetManager.h"

MenuScene::MenuScene(SceneManager* mgr) : m_Manager(mgr), m_Menu(mgr->GetAssets()->GetGameAssets().menuBackground) {}

//void MenuScene::OnEnter() {}

void MenuScene::Update(float dt) {
     MenuAction action = m_Menu.Update();

    if (action == MenuAction::Start)
        m_Manager->Request(SceneType::Game);

    if (action == MenuAction::Quit)
        CloseWindow();
}

void MenuScene::Draw() {
    m_Menu.Draw();
}