#pragma once

#include "raylib.h"
#include "raymath.h"

class InputHandler {
public:
    static Vector2 GetMouseWorld(Camera2D camera);
    static float GetAngleToMouse(Vector2 origin, Camera2D camera);
};