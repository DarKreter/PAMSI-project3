#include "board.hpp"
#include "game.hpp"
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

constexpr size_t windowsSize = 1000;
constexpr size_t borderWidth = 5.f;

int main()
{
    pamsi::Board_t board(windowsSize, borderWidth);

    std::mutex mtx;
    std::thread sfmlLoop(pamsi::sfmlLoop, std::ref(board), std::ref(mtx));
    std::thread realGame(pamsi::Game, std::ref(board), std::ref(mtx));

    sfmlLoop.join();
    realGame.join();

    return 0;
}
