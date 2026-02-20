#include "game.hpp"
#include "Color.hpp"
#include "Window.hpp"
#include "raylib.h"

namespace application {
    Game::Game(int width, int height, const char *title) {
        m_window = raylib::Window(width, height, title);
        m_window.SetConfigFlags(ConfigFlags::FLAG_VSYNC_HINT);
        m_window.Init(width, height, title);
    }

    void Game::Update() {
        dt = m_window.GetFrameTime();
    }
    void Game::Draw() {
        m_window.BeginDrawing();
        m_window.ClearBackground(raylib::Color::RayWhite());
        m_window.EndDrawing();
    }

    void Game::Run() {
        while (!m_window.ShouldClose()) {
            Update();
            Draw();
        }
    }

}// namespace application
