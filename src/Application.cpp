 #include "Application.h"
 #include "log/Logger.h"
 #include "camera/GCamera.h"
 #include "world/World.h"
 #include "character/Player.h"
 #include "character/Zombie.h"
 #include "utilities/AssetManager.h"
 #include "input/InputHandler.h"
 #include "gameplay/Spawner.h"

Application::Application() : m_Window(800, 600, "Raylib Engine") {
  m_Asset = std::make_unique<AssetManager>();

  if(!m_Asset->LoadAll()) {
    Logger::Error("Application failed to start due to missing assets.");
  }

  HideCursor();
  Vector2 startPos = { 1000.0f, 1000.0f };
  
  m_World = std::make_unique<World>("assets/tiles/beach0/straight/0/0.png", 2000, 2000);
  m_Player = std::make_unique<Player>(startPos, m_Asset->GetGameAssets());
  m_Spawner = std::make_unique<Spawner>(m_Player.get(), m_Asset->GetGameAssets());
  m_Camera = std::make_unique<GCamera>(startPos, 800, 600);

  Logger::Info("Application initialized.");
}

Application::~Application() {}

void Application::Run() {
  Logger::Info("Raylib loop started!");
  while (!m_Window.ShouldClose()) {
    Update();
    Draw();
  }
  Logger::Warn("Raylib loop terminating...");
}

void Application::Update() {
  float dt = GetFrameTime();
  auto rayCamera = m_Camera->GetRaylibCamera();

  float rotation = InputHandler::GetAngleToMouse(m_Player->GetPosition(), rayCamera);
  m_Player->SetRotation(rotation);
  m_Player->Update(dt);

  m_Spawner->Update(dt, m_Zombies);

  for(auto& zombie : m_Zombies) {
    zombie->Update(dt);
  }

  // Camera now follows the player object instead of the test point
  auto target = m_Player->GetPosition();
  m_Camera->Follow(target, dt, 5.0f); 
  m_Camera->HandleZoom();
  m_Camera->ClampToWorld({0, 0, 2000, 2000});
}

void Application::Draw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  BeginMode2D(m_Camera->GetRaylibCamera());
  m_World->Draw();
  for(auto& zombie : m_Zombies) {
    zombie->Draw();
  }
  m_Player->Draw();

  Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), m_Camera->GetRaylibCamera());
  const auto& assets = m_Asset->GetGameAssets();
  float crosshairScale = 0.7f;
  Vector2 crosshairPosition = { mouseWorld.x - (assets.crosshair.width * crosshairScale) / 2.0f, mouseWorld.y - (assets.crosshair.height * crosshairScale) / 2.0f };
  DrawTextureEx(assets.crosshair, crosshairPosition, 0.0f, crosshairScale, WHITE);

  EndMode2D();
  DrawFPS(10, 10);
  EndDrawing();
}