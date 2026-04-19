#include "Debug.h"
#include "character/Player.h"
#include "character/Zombie.h"

bool Debug::s_Enabled = false;

void Debug::Init() {
    s_Enabled = false;
}

void Debug::Update() {
#ifdef _DEBUG
    if(IsKeyPressed(KEY_F8)) {
        s_Enabled = !s_Enabled;
    }
#endif
}

bool Debug::IsEnabled() {
#ifdef _DEBUG
    return s_Enabled;
#else
    return false;
#endif
}

void Debug::DrawWorld(Player* player, const std::vector<std::unique_ptr<Zombie>>& zombies) {
#ifndef _DEBUG
    return;
#endif

    if(!s_Enabled) return;

    //Player Debug
    Vector2 playerPos = player->GetPosition();
    DrawCircleLinesV(playerPos, player->GetCollisionRadius(), GREEN);
    DrawText(TextFormat("Player HP: %.1f%%", player->GetHealthPercent() * 100.0f), 20, 40, 20, GREEN);

    //Zombie Debug
    for(const auto& zombie : zombies) {
        Vector2 pos = zombie->GetPosition();
        DrawCircleLinesV(pos, zombie->GetCollisionRadius(), GREEN);
        float barWidth = 40.0f;
        float barHeight = 5.0f;
        Vector2 barPos = {pos.x - barWidth / 2, pos.y - 50};
        DrawRectangleV(barPos, {barWidth, barHeight}, DARKGRAY);
        DrawRectangleV(barPos, {barWidth * zombie->GetHealthPercent(), barHeight}, LIME);
    }
}

void Debug::DrawUI() {
#ifndef _DEBUG
    return;
#endif

    //Global Debug
    DrawFPS(20, 10);
    DrawText("[F8] Debug ON", 20, 10, 20, YELLOW);
}