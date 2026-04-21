#include "GameLevel.h"
#include "character/Player.h"
#include "character/Zombie.h"
#include "gameplay/Spawner.h"
#include "gameplay/GameMode.h"
#include "world/World.h"
#include "camera/GCamera.h"
#include "utilities/AssetManager.h"
#include "gameplay/sound/SoundManager.h"
#include "input/InputHandler.h"
#include "utilities/debug/Debug.h"

GameLevel::GameLevel(const GameAssets& assets) : m_Assets(assets) {
    Vector2 startPos = {1000.0f, 1000.0f};

    m_SoundManager = std::make_unique<SoundManager>();
    m_SoundManager->Init();

    auto& sloader = m_SoundManager->GetLoader();
    sloader.LoadSoundAsset("gunShot", "assets/sounds/pistol-shots_01.wav");
    sloader.LoadSoundAsset("zombie_groan", "assets/sounds/zombie_groan.wav");
    sloader.LoadSoundAsset("hit", "assets/sounds/Hurt.wav");
    sloader.LoadSoundAsset("player_dead", "assets/sounds/Death.wav");

    m_GameMode = std::make_unique<GameMode>();
    m_World = std::make_unique<World>("assets/tiles/beach0/straight/0/0.png", 2000, 2000);
    m_Player = std::make_unique<Player>(startPos, m_Assets, m_SoundManager.get());
    m_Spawner = std::make_unique<Spawner>(m_Player.get(), m_Assets, m_SoundManager.get());
    m_Camera = std::make_unique<GCamera>(startPos, 800, 600);
}

GameLevel::~GameLevel() {
    m_Zombies.clear();
    m_Player.reset();
    m_Spawner.reset();
    m_Camera.reset();
    m_GameMode.reset();
    m_SoundManager.reset();
    m_World.reset();
}

void GameLevel::Update(float dt) {
    if(!m_Player) return;

    auto rayCamera = m_Camera->GetRaylibCamera();

    float rotation = InputHandler::GetAngleToMouse(m_Player->GetPosition(), rayCamera);
    m_Player->SetRotation(rotation);
    m_Player->Update(dt);

    if(m_Player->GetState() == PlayerState::E_Dead) {
        m_GameOver = true;
        m_FinalScore = m_GameMode->GetScore();
        return;
    }

    if(m_GameOver) return;

    m_Spawner->Update(dt, m_Zombies);

    auto& bullets = m_Player->GetBullets();

    for (int i = (int)m_Zombies.size() - 1; i >= 0; i--) {
        m_Zombies[i]->Update(dt);

        for (auto& bullet : bullets) {
            if (!bullet.active) continue;

            if (CheckCollisionPointCircle(bullet.position, m_Zombies[i]->GetPosition(), m_Zombies[i]->GetCollisionRadius())) {
                m_Zombies[i]->TakeDamage(10.0f);
                bullet.active = false;
            }
        }

        if (CheckCollisionCircles(
            m_Zombies[i]->GetPosition(), m_Zombies[i]->GetCollisionRadius(), m_Player->GetPosition(), m_Player->GetCollisionRadius())) {
            m_Player->TakeDamage(30.0f * dt);
        }

        if (m_Zombies[i]->IsDead()) {
            m_GameMode->OnZombieKilled(m_Zombies[i].get());
            m_Zombies.erase(m_Zombies.begin() + i);
        }
    }

    m_GameMode->Update(dt);

    // Camera
    m_Camera->Follow(m_Player->GetPosition(), dt, 5.0f);
    m_Camera->HandleZoom();
    m_Camera->ClampToWorld({0, 0, 2000, 2000});
}

void GameLevel::Draw() {
    BeginMode2D(m_Camera->GetRaylibCamera());

    m_World->Draw();

    for (auto& zombie : m_Zombies) {
        zombie->Draw();
    }
    m_Player->Draw();

    Debug::DrawWorld(m_Player.get(), m_Zombies);

    EndMode2D();

    // UI (crosshair + HUD)
    Vector2 mouse = GetMousePosition();
    Texture2D crosshair = m_Assets.crosshair;
    float scale = 0.5f;
    Rectangle src =  { 0, 0, static_cast<float>(crosshair.width), static_cast<float>(crosshair.height)};
    Rectangle dst = {mouse.x, mouse.y, crosshair.width * scale, crosshair.height * scale};
    Vector2 origin {crosshair.width * scale / 2.0f, crosshair.height * scale / 2.0f};
    DrawTexturePro(crosshair, src, dst, origin, 0.0f, WHITE);
    DrawFPS(10, 10);

    // UI
    float barWidth = 200;
    float barHeight = 20;
    float padding = 20;

    float x = GetScreenWidth() - barWidth - padding;
    float y = padding;

    m_Player->DrawHealthBar(x, y, barWidth, barHeight);

    int score = m_GameMode->GetScore();
    DrawText(TextFormat("Score: %d", score), x, y + 30, 20, WHITE);

    GameOver();

    Debug::DrawUI();
}

void GameLevel::GameOver() {
    if(!m_GameOver) return;

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 180});
    const char* text = "GAME OVER";

    int fontSize = 50;
    int w = GetScreenWidth();
    int h = GetScreenHeight();
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, (w - textWidth)/2, h/2 - 60, fontSize, RED);
    const char* scoreText = TextFormat("Score: %d", m_FinalScore);
    int scoreWidth = MeasureText(scoreText, 30);
    DrawText(scoreText, (w - scoreWidth)/2, h/2, 30, WHITE);
    DrawText("Press ENTER to return to menu", (w - 300)/2, h/2 + 50, 20, YELLOW);
}