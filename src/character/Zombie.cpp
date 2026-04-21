#include "Zombie.h"
#include "Player.h"
#include "gameplay/sound/SoundManager.h"

Zombie::Zombie(Vector2 position, Player* target, const GameAssets& assets, SoundManager* soundMgr) : Character(position, 30.0f, soundMgr), m_Target(target), m_GameAsset(assets) {
    m_CurrentAnimation = &m_GameAsset.zombieWalk;
}

void Zombie::Update(float dt) {
    if(!m_Target) return;
    if(!m_Target->IsDead()) return;

    Vector2 taregtPos = m_Target->GetPosition();
    Vector2 direction = Vector2Subtract(taregtPos, m_Position);

    if(Vector2Length(direction) > 5.0f) {
        m_Rotation = atan2f(direction.y, direction.x) * RAD2DEG;
        direction = Vector2Normalize(direction);
        m_Position = Vector2Add(m_Position, Vector2Scale(direction, m_Speed * dt));
        UpdateAnimation(dt);

        if(m_SoundManager && GetRandomValue(0, 200) == 0) {
            m_SoundManager->PlaySFX("zombie_groan");
        }
    }
}

void Zombie::Draw() {
    if (m_CurrentAnimation->empty()) return;

    Texture2D texture = (*m_CurrentAnimation)[m_FrameX];
    float scaledW = texture.width * m_Scale;
    float scaledH = texture.height * m_Scale;
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Rectangle dest = { m_Position.x, m_Position.y, static_cast<float>(texture.width) * m_Scale, static_cast<float>(texture.height) * m_Scale };
    Vector2 origin = { scaledW / 2.0f, scaledH / 2.0f };
    DrawTexturePro(texture, source, dest, origin, m_Rotation, WHITE);

    float healthBarWidth = 50.0f;
    float healthBarHeight = 6.0f;
    float x = m_Position.x - healthBarWidth / 2.0f;
    float y = m_Position.y - scaledH / 2.0f - 10.0f;
    DrawHealthBar(x, y, healthBarWidth, healthBarHeight);
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

void Zombie::Kill() {
    m_IsAlive = false;
}

float Zombie::GetCollisionRadius() const {
    float baseSize = 80.0f;
    return (baseSize * m_Scale);
}

void Zombie::Reset(Player* newTarget) {
    m_Target = newTarget;
    m_IsAlive = true;
    m_Health = 30.0f;
    m_FrameX = 0;
}