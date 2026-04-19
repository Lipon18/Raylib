#pragma once

#include "raylib.h"
#include <vector>

struct GameAssets {
    // Player Assets
    std::vector<Texture2D> idleFrames;
    std::vector<Texture2D> runFrames;
    std::vector<Texture2D> playerFootSteps;

    // Zombie Assets
    std::vector<Texture2D> zombieWalk;
    
    // UI
    Texture2D crosshair;
    Texture2D menuBackground;
};