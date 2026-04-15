#pragma once

#include "raylib.h"
#include <string>

class GWindow {
    public:
    GWindow(const int width, const int height, const std::string& title);

    ~GWindow();

    bool ShouldClose() const;
};