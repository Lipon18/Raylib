#pragma once

#include "Character.h"
#include "raymath.h"
#include "AssetData.h"

class Player;

class Zombie : public Character {
    public:
    Zombie(Vector2 position, Player* target, const GameAssets& assets, SoundManager* soundMgr);

    void Update(float dt) override;
    void Draw() override;
    void Kill();

    float GetCollisionRadius() const override;

    bool GetIsAlive() const { return m_IsAlive; }
    void SetTarget(Player* player) {m_Target = player;}

    private:
    void UpdateAnimation(float dt);

    bool m_IsAlive = true;

    Player* m_Target = nullptr;
    const GameAssets& m_GameAsset;
    const std::vector<Texture2D>* m_CurrentAnimation;

    float m_Speed = 120.0f;
    float m_Rotation = 0.0f;

    int m_FrameX = 0;
    float m_RunningTime = 0.0f;
    float m_UpdateTime = 1.0f / 12.0f; 
    float m_Scale = 0.5f;

    void Reset(Player* newTarget);
};