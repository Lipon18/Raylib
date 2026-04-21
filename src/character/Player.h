#pragma once

#include "Character.h"
#include "raymath.h"
#include <vector>
#include "../utilities/TextureManager.h"
#include "AssetData.h"

struct Footprint {
    Vector2 position;
    float rotation;
    float alpha;
    int textureIdx;
};

struct Bullet {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    bool active;
};

enum class PlayerState {
    E_Alive,
    E_Dead
};

class Player : public Character {
    public:
    Player(Vector2 position, const GameAssets& assets, SoundManager* soundMgr);

    void Update(float dt) override;
    void Draw() override;
    virtual void OnDeath() override;

    void DrawHealthBar(float x, float y, float width, float height) const;

    float GetCollisionRadius() const override {return 70.0f * m_Scale;}
    PlayerState GetState() const {return m_State;}

    std::vector<Bullet>& GetBullets() {return m_Bullets;}
    void SetRotation(float rotation) {m_Rotation = rotation;}

    private:
    void HandleInput(float dt);
    void UpdateAnimation(float dt);

    const GameAssets& m_Assets;
    const std::vector<Texture2D>* m_CurrentAnimation;

    PlayerState m_State = PlayerState::E_Alive;
    bool m_DeathHandled = false;

    std::vector<Footprint> m_Footprints;
    float m_FootstepTimer = 0.0f;
    float m_FootstepInterval = 0.2f;

    std::vector<Bullet> m_Bullets;
    float m_ShootTimer = 0.0f;
    float m_ShootCooldown = 0.25f;
    float m_BulletSpeed = 800.0f;

    int m_FrameX = 0;
    float m_RunningTime = 0.0f;
    float m_UpdateTime = 1.0f/ 10.0f;
    float m_Scale = 0.5f;
    float m_Speed = 300.0f;
    bool m_FacingRight = true;

    float m_Rotation = 0.0f;
    Vector2 m_MousePos;

    void UpdateFootprints(float dt);
    void CreateFootprint();
    void HandleShooting(float dt);
    void UpdateBullets(float dt);
    void UpdateAlive(float dt);
    void UpdateDead(float dt);

    Texture2D GetCurrentFrame() const;

    Vector2 m_MuzzleDebugPos = { 0, 0 };
    float m_MuzzleForward = 90.0f;
    float m_MuzzleSide = 60.0f;
};