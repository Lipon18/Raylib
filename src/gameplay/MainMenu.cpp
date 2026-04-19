#include "MainMenu.h"

// bool MainMenu::ShouldStartGame() const {
//     return IsKeyPressed(KEY_ENTER);
// }

// bool MainMenu::ShouldQuitGame() const {
//     return IsKeyPressed(KEY_ESCAPE);
// }

MainMenu::MainMenu(const Texture2D& background) : m_Background(background) {}

void MainMenu::UpdateLayout() {
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    
    m_PlayButton = { screenW / 2.0f - 100, screenH / 2.0f, 200, 60};
    m_QuitButton = {screenW / 2.0f - 100, screenH / 2.0f + 80, 200, 60};
}

MenuAction MainMenu::Update() {
    UpdateLayout();

    Vector2 mouse = GetMousePosition();

    // keyboard input
    if (IsKeyPressed(KEY_ENTER)) return MenuAction::Start;
    if (IsKeyPressed(KEY_ESCAPE)) return MenuAction::Quit;

    // mouse input
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, m_PlayButton))
            return MenuAction::Start;

        if (CheckCollisionPointRec(mouse, m_QuitButton))
            return MenuAction::Quit;
    }

    return MenuAction::None;
}

void MainMenu::Draw() {
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    DrawTexturePro(m_Background, { 0, 0, static_cast<float>(m_Background.width),  static_cast<float>(m_Background.height) }, {0, 0, static_cast<float>(screenW), static_cast<float>(screenH)}, {0, 0}, 0.0f, WHITE);

    const char* title = "Wasted Flesh Game";

    DrawText(
        title,
        screenW / 2 - MeasureText(title, 40) / 2,
        screenH / 4,
        40,
        WHITE
    );

    Vector2 mouse = GetMousePosition();

    bool playHover = CheckCollisionPointRec(mouse, m_PlayButton);
    bool quitHover = CheckCollisionPointRec(mouse, m_QuitButton);

    DrawRectangleRec(m_PlayButton, playHover ? DARKGREEN : GREEN);
    DrawText("PLAY", m_PlayButton.x + (m_PlayButton.width - MeasureText("PLAY", 20)) / 2, m_PlayButton.y + 20, 20, WHITE);

    DrawRectangleRec(m_QuitButton, quitHover ? MAROON : RED);
    DrawText("QUIT", m_QuitButton.x + (m_QuitButton.width - MeasureText("QUIT", 20)) / 2, m_QuitButton.y + 20, 20, WHITE);
}