#pragma once

#include "raylib.h"
#include <unordered_map>
#include <string>
#include <iostream>

class SoundLoader {
public:
    bool LoadSoundAsset(const std::string& name, const std::string& path);
    bool LoadMusicAsset(const std::string& name, const std::string& path);

    Sound& GetSound(const std::string& name) {return m_Sounds.at(name);}
    Music& GetMusic(const std::string& name) {return m_Music.at(name);}

    void UnloadAll();

private:
    std::unordered_map<std::string, Sound> m_Sounds;
    std::unordered_map<std::string, Music> m_Music;

};