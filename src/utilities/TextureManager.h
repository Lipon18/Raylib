#pragma once

#include "raylib.h"
#include <vector>
#include <string>

class TextureManager {
    public:
    static std::vector<Texture2D> LoadFlipbook(const std::string& basePath, const std::string& prefix, int frameCount) {
        std::vector<Texture2D> frames;
        for (int i = 0; i < frameCount; i++) {
            std::string path = basePath + prefix + std::to_string(i) + ".png";
            frames.push_back(LoadTexture(path.c_str()));
        }
        return frames;
    }

    static void UnloadFlipbook(std::vector<Texture2D>& frames) {
        for (auto& tex : frames) UnloadTexture(tex);
        frames.clear();
    }
};