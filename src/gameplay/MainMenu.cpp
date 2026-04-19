#include "MainMenu.h"
#include "raylib.h"

bool MainMenu::ShouldStartGame() const {
    return IsKeyPressed(KEY_ENTER);
}

bool MainMenu::ShouldQuitGame() const {
    return IsKeyPressed(KEY_ESCAPE);
}

void MainMenu::Draw() {
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    extern Texture2D g_MenuBackground;

    DrawTexturePro(
        g_MenuBackground,
        {0, 0, (float)g_MenuBackground.width, (float)g_MenuBackground.height},
        {0, 0, (float)screenW, (float)screenH},
        {0, 0},
        0.0f,
        WHITE
    );

    const char* title = "Wasted Flesh Game";
    DrawText(title,
        screenW / 2 - MeasureText(title, 40) / 2,
        screenH / 4,
        40,
        WHITE
    );

    m_PlayButton = {
        screenW / 2.0f - 100,
        screenH / 2.0f,
        200,
        60
    };

    m_QuitButton = {
        screenW / 2.0f - 100,
        screenH / 2.0f + 80,
        200,
        60
    };

    Vector2 mouse = GetMousePosition();

    bool playHover = CheckCollisionPointRec(mouse, m_PlayButton);
    bool quitHover = CheckCollisionPointRec(mouse, m_QuitButton);

    DrawRectangleRec(m_PlayButton, playHover ? DARKGREEN : GREEN);
    DrawText("PLAY",
        m_PlayButton.x + 70,
        m_PlayButton.y + 20,
        20,
        WHITE
    );

     DrawRectangleRec(m_QuitButton, quitHover ? MAROON : RED);
    DrawText("QUIT",
        m_QuitButton.x + 70,
        m_QuitButton.y + 20,
        20,
        WHITE
    );

    // const char* hint  = "Press ENTER or Click to Start";
    // int titleSize = 40;
    // int hintSize = 20;
    // int screenW = GetScreenWidth();
    // int screenH = GetScreenHeight();
    
    // DrawText(title, screenW/2 - MeasureText(title, titleSize)/2, screenH/2 - 40, titleSize, WHITE);
    // DrawText(hint, screenW/2 - MeasureText(hint, hintSize)/2, screenH/2 + 10, hintSize, GRAY);
}

MenuAction MainMenu::Update() {
    Vector2 mouse = GetMousePosition();

    if (IsKeyPressed(KEY_ENTER)) return MenuAction::Start;
    if (IsKeyPressed(KEY_ESCAPE)) return MenuAction::Quit;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, m_PlayButton)) return MenuAction::Start;
        if (CheckCollisionPointRec(mouse, m_QuitButton)) return MenuAction::Quit;
    }
    return MenuAction::None;
}