    #pragma once

    #include "raylib.h"

    class Scene {
    public:
        virtual ~Scene() = default;

        virtual void OnEnter() {}
        virtual void OnExit() {}

        virtual void Update(float dt) = 0;
        virtual void Draw() =0;
    };