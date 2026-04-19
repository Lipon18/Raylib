#include "SceneManager.h"
#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "utilities/AssetManager.h"

void SceneManager::Init(AssetManager* assets) {
    m_Assets = assets;
    Change(SceneType::Menu);
}

void SceneManager::Request(SceneType type) {
    m_Next = type;
    m_HasRequest = true;
}

void SceneManager::Change(SceneType type) {
     if (m_Current) {
        m_Current->OnExit();
        m_Current.reset();
    }
    switch (type) {
        case SceneType::Menu:
            m_Current = std::make_unique<MenuScene>(this);
            break;

        case SceneType::Game:
            m_Current = std::make_unique<GameScene>(this);
            break;

        case SceneType::Pause:
            m_Current = std::make_unique<PauseScene>(this);
            break;
    }
    m_Current->OnEnter();
}

void SceneManager::Update(float dt) {
   if (m_Current)
        m_Current->Update(dt);

    if (m_HasRequest) {
        Change(m_Next);
        m_HasRequest = false;
    }
}

void SceneManager::Draw() {
   if (m_Current) m_Current->Draw();
}