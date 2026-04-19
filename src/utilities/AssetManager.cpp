#include "AssetManager.h"
#include "../log/Logger.h"

bool AssetManager::LoadAll() {
    m_GameAssets.crosshair = LoadTexture("assets/crosshair/PNG/White/crosshair075.png");

   if (m_GameAssets.crosshair.id == 0) {
        Logger::Error("Failed to load crosshair texture! Check your file path.");
        return false;
    }

    m_GameAssets.menuBackground = LoadTexture("assets/cover_image/Wasted_Flesh_TopDown_Artwork.png");
    if (m_GameAssets.menuBackground.id == 0) {
        Logger::Error("Failed to load menu background!");
        return false;
    }
    
    m_GameAssets.idleFrames = TextureManager::LoadFlipbook("assets/Top_Down_Survivor/handgun/idle/", "survivor-idle_handgun_", 20);
    m_GameAssets.runFrames = TextureManager::LoadFlipbook("assets/Top_Down_Survivor/handgun/move/", "survivor-move_handgun_", 20);
    m_GameAssets.playerFootSteps = TextureManager::LoadFlipbook("assets/Top_Down_Survivor/feet/run/", "survivor-run_", 20);
    m_GameAssets.zombieWalk = TextureManager::LoadFlipbook("assets/zombie/export/move/", "skeleton-move_", 10);

    if(m_GameAssets.idleFrames.empty() || m_GameAssets.runFrames.empty() || m_GameAssets.playerFootSteps.empty() ||m_GameAssets.zombieWalk.empty()) {
        Logger::Error("Failed to load one or more animations!");
        return false;
    }
    return true;
}

AssetManager::~AssetManager() {
    UnloadTexture(m_GameAssets.crosshair);
    TextureManager::UnloadFlipbook(m_GameAssets.idleFrames);
    TextureManager::UnloadFlipbook(m_GameAssets.runFrames);
    TextureManager::UnloadFlipbook(m_GameAssets.zombieWalk);
    TextureManager::UnloadFlipbook(m_GameAssets.playerFootSteps);
    Logger::Info("Assets unloaded.");    
}