  #include "Application.h"
  #include "log/Logger.h"
  #include "scene/SceneManager.h"
  #include "scene/MenuScene.h"
  #include "utilities/AssetManager.h"
  #include "utilities/debug/Debug.h"

  Application::Application() : m_Window(800, 600, "Raylib Engine!") {
    m_Asset = std::make_unique<AssetManager>();

    if (!m_Asset->LoadAll()) {
      Logger::Error("Failed to load assets");
    }

    m_SceneManager  = std::make_unique<SceneManager>();
    m_SceneManager->Init(m_Asset.get());

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
    m_SceneManager->Update(dt);
    Debug::Update();
  }

  void Application::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    m_SceneManager->Draw();
    EndDrawing();
  }