#include "SoundManager.h"

SoundManager::SoundManager() {}

bool SoundManager::Init() {
    InitAudioDevice();
    SetMasterVolume(1.0f);
    return true;
}

void SoundManager::Update() {
    if (m_CurrentMusic) {
        UpdateMusicStream(*m_CurrentMusic);
    }
}

void SoundManager::PlaySFX(const std::string& name) {
    Sound& s = m_Loader.GetSound(name);
    SetSoundVolume(s, m_SFXVolume);
    PlaySound(s);
}

void SoundManager::PlayMusicTrack(const std::string& name, bool loop) {
    if (m_CurrentMusic) {
        StopMusicStream(*m_CurrentMusic);
    }

    m_CurrentMusic = &m_Loader.GetMusic(name);
    SetMusicVolume(*m_CurrentMusic, m_MusicVolume);
    m_CurrentMusic->looping = loop;

    PlayMusicStream(*m_CurrentMusic);
}

void SoundManager::StopMusic() {
    if (m_CurrentMusic) {
        StopMusicStream(*m_CurrentMusic);
        m_CurrentMusic = nullptr;
    }
}

void SoundManager::SetMusicVolumeLevel(float volume) {
    m_MusicVolume = volume;
    if (m_CurrentMusic) {
        SetMusicVolume(*m_CurrentMusic, volume);
    }
}