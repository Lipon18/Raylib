    #pragma once

    #include "raylib.h"

    class Character {
        public:
        Character(Vector2 position, float maxHealth) : m_Position(position), m_MaxHealth(maxHealth) { m_Health = ClampHealth(maxHealth); }
        virtual ~Character() {}
        virtual void Update(float dt) = 0;
        virtual void Draw() = 0;
        virtual float GetCollisionRadius() const { return 20.0f; }

        void TakeDamage(float amount) {
            if(amount <= 0.0f) return;
            ModifyHealth(-amount);
        }

        float GetHealthPercent() const { 
            if(m_MaxHealth <= 0.0f) return 0.0f; 
            return ClampHealth(m_Health) / m_MaxHealth;
        }

        bool IsDead() const {return m_Health <= 0.0f;}
        
        Vector2 GetPosition() const {return m_Position;}
        void SetPosition(Vector2 pos) {m_Position = pos;}

        protected:
        Vector2 m_Position;
        float m_MaxHealth;
        float m_Health;


        void ModifyHealth(float amount) {
            m_Health = ClampHealth(m_Health + amount);
        }

        float ClampHealth(float value) const {
            if(value < 0.0f) return 0.0f;
            if(value > m_MaxHealth) return m_MaxHealth;
            return value;
        }

        virtual void DrawHealthBar(float x, float y, float width, float height) const {
            float healthPercent = GetHealthPercent();

            DrawRectangle(x, y, width, height, DARKGRAY);

            Color healthColor;
            if(healthPercent > 0.6f) healthColor = GREEN;
            else if (healthPercent > 0.3f) healthColor = ORANGE;
            else healthColor = RED;
            DrawRectangle(x, y, width * healthPercent, height, healthColor);
            DrawRectangleLines(x, y, width, height, BLACK);
        }
    };