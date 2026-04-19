#pragma once

#include "raylib.h"
#include <vector>
#include <memory>

class Player;
class Zombie;

class Debug {
    public:
    static void Init();
    static void Update();
    static bool IsEnabled();
    static void DrawWorld(Player* player, const std::vector<std::unique_ptr<Zombie>>& zombies);
    static void DrawUI();

    private:
    static bool s_Enabled;
};