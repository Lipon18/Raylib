 #include "Application.h"
 #include "log/Logger.h"

 Application::Application() : m_Window(800, 600, "Raylib Engine") {
   Logger::Info("Application initialized.");
 }

 void Application::Run() {
   Logger::Info("Raylib loop started!");
   while (!m_Window.ShouldClose()) {
      Update();
      Draw();
   }
   Logger::Warn("Raylib loop terminating...");
 }

 void Application::Update() {

 }

 void Application::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Raylib!", 300, 280, 20, BLACK);
    EndDrawing();
 }