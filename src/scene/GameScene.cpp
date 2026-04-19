    #include "GameScene.h"
    #include "SceneManager.h"
    #include "gameplay/GameLevel.h"
    #include "utilities/AssetManager.h"
    #include "raylib.h"

    GameScene::GameScene(SceneManager* mgr) : m_Manager(mgr), m_Assets(mgr->GetAssets()->GetGameAssets()) {}

    GameScene::~GameScene() {
        delete m_Level;
    }

    void GameScene::OnEnter() {
         m_Level = new GameLevel(m_Assets);
    }

    void GameScene::Update(float dt) {
        if (IsKeyPressed(KEY_P)) {
            m_Manager->Request(SceneType::Pause);
            return;
        }

        if (m_Level) m_Level->Update(dt);
    }

    void GameScene::Draw() {
        if(m_Level) m_Level->Draw();
    }