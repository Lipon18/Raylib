#pragma once
#include "SoundLoader.h"
#include <string>

class SoundManager {
public:
    SoundManager();

    bool Init();
    void Update(); // important for music streaming

    void PlaySFX(const std::string& name);
    void PlayMusicTrack(const std::string& name, bool loop = true);

    void StopMusic();
    void SetMusicVolumeLevel(float volume);
    void SetSFXVolumeLevel(float volume) {m_SFXVolume = volume;}

    SoundLoader& GetLoader() {return m_Loader;}

private:
    SoundLoader m_Loader;

    float m_MusicVolume = 1.0f;
    float m_SFXVolume = 1.0f;

    Music* m_CurrentMusic = nullptr;
};