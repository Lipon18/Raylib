#include "Zombie.h"
#include "Player.h"

Zombie::Zombie(Vector2 position, Player* target, const GameAssets& assets) : Character(position), m_Target(target), m_GameAsset(assets) {
    m_CurrentAnimation = &m_GameAsset.zombieWalk;
}

void Zombie::Update(float dt) {
    if(!m_Target) return;

    Vector2 taregtPos = m_Target->GetPosition();
    Vector2 direction = Vector2Subtract(taregtPos, m_Position);

    if(Vector2Length(direction) > 5.0f) {
        m_Rotation = atan2f(direction.y, direction.x) * RAD2DEG;
        direction = Vector2Normalize(direction);
        m_Position = Vector2Add(m_Position, Vector2Scale(direction, m_Speed * dt));
        UpdateAnimation(dt);
    }
}

void Zombie::Draw() {
    if (m_CurrentAnimation->empty()) return;

    Texture2D texture = (*m_CurrentAnimation)[m_FrameX];
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Rectangle dest = { m_Position.x, m_Position.y, static_cast<float>(texture.width) * m_Scale, static_cast<float>(texture.height) * m_Scale };
    Vector2 origin = { (texture.width * m_Scale) / 2.0f, (texture.height * m_Scale) / 2.0f };
    DrawTexturePro(texture, source, dest, origin, m_Rotation, WHITE);
}

void Zombie::UpdateAnimation(float dt) {
    m_RunningTime += dt;
    if(m_RunningTime >= m_UpdateTime) {
        m_RunningTime = 0.0f;
        m_FrameX++;
        if(m_FrameX >= static_cast<int>(m_CurrentAnimation->size())) {
            m_FrameX = 0;
        }
    }
}