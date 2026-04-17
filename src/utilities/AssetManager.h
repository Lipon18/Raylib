#pragma once

#include "raylib.h"
#include <vector>
#include <string>
#include "TextureManager.h"
#include "character/AssetData.h"

class AssetManager {
    public:
    AssetManager() = default;
    ~AssetManager();

    bool LoadAll();

    const GameAssets& GetGameAssets() const {return m_GameAssets;}

    private:
    GameAssets m_GameAssets;
};