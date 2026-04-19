  #include "Application.h"
  #include "log/Logger.h"
  #include "gameplay/MainMenu.h"
  #include "gameplay/GameLevel.h"
  #include "utilities/AssetManager.h"
  #include "utilities/debug/Debug.h"

  Application::Application() : m_Window(800, 600, "Raylib Engine!"), m_State(AppState::Menu) {
    m_Asset = std::make_unique<AssetManager>();

    if (!m_Asset->LoadAll()) {
      Logger::Error("Failed to load assets");
    }

    m_Menu = std::make_unique<MainMenu>();

    Logger::Info("Application initialized.");
    Debug::Init();
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

    if(m_State == AppState::Menu) {
      if(m_Menu->ShouldStartGame() || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(),  Rectangle{ GetScreenWidth()/2.0f - 100,
        GetScreenHeight()/2.0f, 200, 60 }))) {
        m_GameLevel = std::make_unique<GameLevel>(m_Asset->GetGameAssets());
        m_State = AppState::Playing;
        HideCursor();
      }
      if(m_Menu->ShouldQuitGame() || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), Rectangle{ GetScreenWidth()/2.0f - 100, 
        GetScreenHeight()/2.0f + 80, 200, 60 }))) {
          CloseWindow();
        }
    }
    else if (m_State == AppState::Playing) {
      m_GameLevel->Update(dt);
    }
    Debug::Update();
  }

  void Application::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if(m_State == AppState::Menu) {
      m_Menu->Draw();
    }
    else if (m_State == AppState::Playing) {
      m_GameLevel->Draw();
    }

    EndDrawing();
  }