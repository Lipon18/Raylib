#include "GCamera.h"

 GCamera::GCamera(Vector2 target, int screenWidth, int screenHeight) {
    m_Camera.target = target;
    m_Camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    m_Camera.rotation = 0.0f;
    m_Camera.zoom = 1.0f;
 }

void GCamera::SetTarget(Vector2 target) {
    m_Camera.target = target;
}

void GCamera::Follow(Vector2 target, float deltaTime, float lerpSpeed) {
    m_Camera.target.x += (target.x - m_Camera.target.x) * lerpSpeed * deltaTime;
    m_Camera.target.y += (target.y - m_Camera.target.y) * lerpSpeed * deltaTime;
}

void GCamera::HandleZoom(){
    float wheel = GetMouseWheelMove();
    if(wheel != 0) {
        m_Camera.zoom += wheel * m_ZoomSpeed;
        if(m_Camera.zoom < 0.5f) m_Camera.zoom = 0.5f;
        if(m_Camera.zoom > 30.f) m_Camera.zoom = 3.0f;
    }
}

void GCamera::ClampToWorld(Rectangle bounds) {
    Vector2 min = { bounds.x + m_Camera.offset.x / m_Camera.zoom, bounds.y + m_Camera.offset.y / m_Camera.zoom };
    Vector2 max = { bounds.x + bounds.width - m_Camera.offset.x / m_Camera.zoom, bounds.y + bounds.height - m_Camera.offset.y / m_Camera.zoom };

    if (m_Camera.target.x < min.x) m_Camera.target.x = min.x;
    if (m_Camera.target.x > max.x) m_Camera.target.x = max.x;
    if (m_Camera.target.y < min.y) m_Camera.target.y = min.y;
    if (m_Camera.target.y > max.y) m_Camera.target.y = max.y;
}