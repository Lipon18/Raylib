#pragma once

#include "raylib.h"
#include <string>

class World {
    public:
    World(const std::string& texturePath, int worldWidth, int worldHeight);
    ~World();

    void Draw();
    Vector2 GetCenter() const;

    private:
    Texture2D m_TileTexture;
    int m_WorldWidth;
    int m_WorldHeight;
    int m_TileSize;
};