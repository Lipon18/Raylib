#pragma once
#include <memory>

class Scene;
class AssetManager;

enum class SceneType {
    Menu,
    Game,
    Pause
};

class SceneManager {
public:
    void Init(AssetManager* assets);

    void Request(SceneType type);

    void Update(float dt);
    void Draw();

    AssetManager* GetAssets() const { return m_Assets; }

private:
    void Change(SceneType type);

    std::unique_ptr<Scene> m_Current;
    AssetManager* m_Assets = nullptr;

    SceneType m_Next;
    bool m_HasRequest = false;
};