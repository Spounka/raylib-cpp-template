#ifndef INCLUDE_SRC_GAME_HPP_
#define INCLUDE_SRC_GAME_HPP_

#include <Window.hpp>

namespace application {
    class Game {
    public:
        Game(int width, int height, const char *title);
        ~Game() = default;

        void Run();

    private:
        raylib::Window m_window{};
        double dt;

    private:
        void Update();
        void Draw();
    };
}// namespace application

#endif// INCLUDE_SRC_GAME_HPP_
