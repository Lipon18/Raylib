    #include "GameScene.h"
    #include "SceneManager.h"
    #include "gameplay/GameLevel.h"
    #include "utilities/AssetManager.h"
    #include "raylib.h"

    GameScene::GameScene(SceneManager* mgr) : m_Manager(mgr), m_Assets(mgr->GetAssets()->GetGameAssets()) {}

    GameScene::~GameScene() = default;

    void GameScene::OnEnter() {
        m_Level = std::make_unique<GameLevel>(m_Assets);
    }

    void GameScene::Update(float dt) {
        if (IsKeyPressed(KEY_P)) {
            m_Manager->Request(SceneType::Pause);
            return;
        }

        if (m_Level) m_Level->Update(dt);

        if(m_Level && m_Level ->IsGameOver() && IsKeyPressed(KEY_ENTER)) {
            m_Level.reset();
            m_Manager->Request(SceneType::Menu);
            return;
        }  
        // if(m_Level->IsGameOver()) {
        //     m_Manager->Request(SceneType::Menu);
        // }
    }

    void GameScene::Draw() {
        if(m_Level) m_Level->Draw();
    }