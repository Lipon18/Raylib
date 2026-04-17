#include "Player.h"

Player::Player(Vector2 position, const GameAssets& assets)  : Character(position),m_Assets(assets) {
    m_CurrentAnimation = &m_Assets.idleFrames;
    m_Footprints.reserve(64);
}

void Player::Update(float dt) {
    HandleInput(dt);
    HandleShooting(dt);
    UpdateAnimation(dt);
    UpdateFootprints(dt);
    UpdateBullets(dt);
}

void Player::Draw() {
    // Footprints
    for(const auto& footprint : m_Footprints) {
        Texture2D tex = m_Assets.playerFootSteps[footprint.textureIdx];
        Color tint = Fade(WHITE, footprint.alpha * 0.5f);
        float footprintScale = 0.3f;
        Rectangle source = { 0.0f, 0.0f, static_cast<float>(tex.width), static_cast<float>(tex.height) };
        Rectangle dest = { footprint.position.x,  footprint.position.y, static_cast<float>(tex.width) * footprintScale, static_cast<float>(tex.height) * footprintScale }; 
        Vector2 origin = { (tex.width * footprintScale) / 2.0f, (tex.height * footprintScale) / 2.0f };
        DrawTexturePro(tex, source, dest, origin, footprint.rotation, tint);
    }

    for(const auto& bullet : m_Bullets) {
        if(bullet.active) {
            DrawCircleV(bullet.position, 5.0f, YELLOW);
            DrawCircleV(bullet.position, 2.5f, WHITE);
            Vector2 trailPos = Vector2Subtract(bullet.position, Vector2Scale(Vector2Normalize(bullet.velocity), 8.0f));
            DrawCircleV(trailPos, 3.0f, ORANGE);
        }
    }

    if (m_CurrentAnimation->empty()) return;

    Texture2D texture = (*m_CurrentAnimation)[m_FrameX];
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Rectangle dest = { m_Position.x, m_Position.y, static_cast<float>(texture.width) * m_Scale, static_cast<float>(texture.height) * m_Scale }; 
    Vector2 origin = { (texture.width * m_Scale) / 2.0f, (texture.height * m_Scale) / 2.0f };
    DrawTexturePro(texture, source, dest, origin, m_Rotation, WHITE);

    DrawCircleV(m_MuzzleDebugPos, 3.0f, RED);
    DrawLineV(m_Position, m_MuzzleDebugPos, RED);
}

void Player::UpdateAnimation(float dt) {
    m_RunningTime += dt;
    if(m_RunningTime >= m_UpdateTime) {
        m_RunningTime = 0.0f;
        m_FrameX++;
        if(m_FrameX >= static_cast<int>(m_CurrentAnimation->size())) {
            m_FrameX = 0;
        }
    }
}

void Player::HandleInput(float dt) {
    Vector2 direction = { 0, 0 };
    if (IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_S)) direction.y += 1;
    if (IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_D)) direction.x += 1;

    if (IsKeyPressed(KEY_SPACE)) {
        printf("Current Muzzle: Fwd: %f, Side: %f\n", m_MuzzleForward, m_MuzzleSide);
    }

    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
        m_Position = Vector2Add(m_Position, Vector2Scale(direction, m_Speed * dt));

        // Switch to Run
        if (m_CurrentAnimation != &m_Assets.runFrames) {
            m_CurrentAnimation = (std::vector<Texture2D>*)&m_Assets.runFrames;
            m_FrameX = 0;
        }
        if (direction.x < 0) m_FacingRight = false;
        else if (direction.x > 0) m_FacingRight = true;
         m_FootstepTimer += dt;
    if(m_FootstepTimer >= m_FootstepInterval) {
        CreateFootprint();
        m_FootstepTimer = 0.0f;
    }
    } else {
        // Switch to Idle
        if (m_CurrentAnimation != &m_Assets.idleFrames) {
            m_CurrentAnimation = (std::vector<Texture2D>*)&m_Assets.idleFrames;
            m_FrameX = 0;
        }
    }
}

void Player::UpdateFootprints(float dt) {
    for (int i = m_Footprints.size() - 1; i >= 0; i--) {
        m_Footprints[i].alpha -= dt * 0.5f; 

        if (m_Footprints[i].alpha <= 0) {
            m_Footprints.erase(m_Footprints.begin() + i);
        }
    }
}

void Player::CreateFootprint() {
    static bool leftFoot = true; 
    Footprint fp;
    float offsetDist = 10.0f;
    float angle = (m_Rotation + (leftFoot ? 90.0f : -90.0f)) * DEG2RAD;
    fp.position.x = m_Position.x + cosf(angle) * offsetDist;
    fp.position.y = m_Position.y + sinf(angle) * offsetDist;
    fp.rotation = m_Rotation;
    fp.alpha = 1.0f;
    fp.textureIdx = GetRandomValue(0, m_Assets.playerFootSteps.size() - 1);
    m_Footprints.push_back(fp);
    leftFoot = !leftFoot;
}

void Player::HandleShooting(float dt) {
    if (m_ShootTimer > 0) m_ShootTimer -= dt;

    float rad = m_Rotation * DEG2RAD;

    float cosR = cosf(rad);
    float sinR = sinf(rad);

    m_MuzzleDebugPos.x = m_Position.x + (cosR * m_MuzzleForward * m_Scale) - (sinR * m_MuzzleSide * m_Scale);
    m_MuzzleDebugPos.y = m_Position.y + (sinR * m_MuzzleForward * m_Scale) + (cosR * m_MuzzleSide * m_Scale);

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && m_ShootTimer <= 0) {
        Bullet newBullet;
        newBullet.position = m_MuzzleDebugPos;
        newBullet.rotation = m_Rotation;
        newBullet.active = true;
        newBullet.velocity = Vector2Scale({cosR, sinR}, m_BulletSpeed);

        m_Bullets.push_back(newBullet);
        m_ShootTimer = m_ShootCooldown;
    }
}

void Player::UpdateBullets(float dt) {
    for (int i = m_Bullets.size() - 1; i >= 0; i--) {
        m_Bullets[i].position = Vector2Add(m_Bullets[i].position, Vector2Scale(m_Bullets[i].velocity, dt));

        // e.g., 2000 units
        if (Vector2Distance(m_Position, m_Bullets[i].position) > 2000.0f) {
            m_Bullets.erase(m_Bullets.begin() + i);
        }
    }
}