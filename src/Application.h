#pragma once

#include "window/GWindow.h"
#include <memory>
#include <vector>
#include "utilities/TextureManager.h"
#include "character/AssetData.h"

class SceneManager;
class AssetManager;
class SoundManager;

class Application {
    public:
    Application();
    ~Application();

    void Run();
    void Update();
    void Draw();

    private:
    GWindow m_Window;

    std::unique_ptr<AssetManager> m_Asset;
    std::unique_ptr<SceneManager> m_SceneManager;
    std::unique_ptr<SoundManager> m_SoundManager;
};