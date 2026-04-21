#include "SoundLoader.h"
#include "log/Logger.h"

bool SoundLoader::LoadSoundAsset(const std::string& name, const std::string& path) {
    Sound sound = LoadSound(path.c_str());
    if(sound.frameCount == 0) {
        Logger::Error("Failed to load sound");
        std::cout << "Failed to load sound: " << path << "\n";
        return false;
    }
    m_Sounds[name] = sound;
    return true;
}

bool SoundLoader::LoadMusicAsset(const std::string& name, const std::string& path) {
    Music music = LoadMusicStream(path.c_str());
    if(music.frameCount == 0) {
        Logger::Error("Failed to load music");
        std::cout << "Failed to load music: " << path << "\n";
        return false;
    }
    m_Music[name] = music;
    return true;
}

void SoundLoader::UnloadAll() {
    for(auto& [_, sound] : m_Music) {
        UnloadMusicStream(sound);
    }

    for(auto& [_, music] : m_Music) {
        UnloadMusicStream(music);
    }
}