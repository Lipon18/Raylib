    #pragma once

    #include "raylib.h"

    class Character {
        public:
        Character(Vector2 position) : m_Position(position) {}
        virtual ~Character() {}
        virtual void Update(float dt) = 0;
        virtual void Draw() = 0;

        Vector2 GetPosition() const {return m_Position;}
        void SetPosition(Vector2 pos) {m_Position = pos;}

        protected:
        Vector2 m_Position;
    };