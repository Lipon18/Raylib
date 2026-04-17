#include "InputHandler.h"

Vector2 InputHandler::GetMouseWorld(Camera2D camera) {
    return GetScreenToWorld2D(GetMousePosition(), camera);
}

float InputHandler::GetAngleToMouse(Vector2 origin, Camera2D camera) {
    Vector2 mouseWorld = GetMouseWorld(camera);
    float dx = mouseWorld.x - origin.x;
    float dy = mouseWorld.y - origin.y;
    return atan2f(dy, dx) * RAD2DEG;
}