#include "GWindow.h"

GWindow::GWindow(const int width, const int height, const std::string& title) {
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
}

GWindow::~GWindow() {
    CloseWindow();
}

bool GWindow::ShouldClose() const {
    return WindowShouldClose();
}