#include "World.h"
#include "../log/Logger.h"

World::World(const std::string& texturePath, int worldWidth, int worldHeight) : m_WorldWidth(worldWidth), m_WorldHeight(worldHeight) {
    m_TileTexture = LoadTexture(texturePath.c_str());

    if(m_TileTexture.id == 0) {
        Logger::Error("Could not load texture: " + texturePath);
        m_TileSize = 64;
    }
    else {
        m_TileSize = m_TileTexture.width;
        Logger::Info("Loaded world textures: " + texturePath + " (" + std::to_string(m_TileSize) + "px)");
    }
    
}

World::~World() {
    if(m_TileTexture.id != 0 ) {
        UnloadTexture(m_TileTexture);
    }
}

void World::Draw() {
    if (m_TileSize <= 0) return;

    for (int x = 0; x < m_WorldWidth; x += m_TileSize) {
        for (int y = 0; y < m_WorldHeight; y += m_TileSize) {
            if (m_TileTexture.id != 0) {
                DrawTexture(m_TileTexture, x, y, WHITE);
            } 
            else {
                DrawRectangleLines(x, y, m_TileSize, m_TileSize, RED);
            }
        }
    }
}

Vector2 World::GetCenter() const {
    return { static_cast<float>(m_WorldWidth) / 2.0f, static_cast<float>(m_WorldHeight) / 2.0f };
}