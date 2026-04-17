#pragma once

#include "raylib.h"

class GCamera {
    public:
    GCamera(Vector2 target, int screenWidth, int screenHeight);

    void SetTarget(Vector2 target);
    void Follow(Vector2 target, float deltaTime, float lerpSpeed = 5.0f);
    void HandleZoom();
    void ClampToWorld(Rectangle bounds);
    
    Camera2D GetRaylibCamera() const {return m_Camera;}

    private:
    Camera2D m_Camera;
    float m_ZoomSpeed = 0.1f;
};