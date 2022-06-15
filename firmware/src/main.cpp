#include "Algorithms.hpp"
#include "board.hpp"
#include "game.hpp"
#include <X11/Xlib.h>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

constexpr size_t windowsSize = 1000;
constexpr size_t borderWidth = 5.f;

int main()
{
    XInitThreads();
    pamsi::Board_t board(windowsSize, borderWidth);
    std::queue<sf::Vector2u> mouseQueue;
    bool reading = false;
    std::mutex queueMutex;

    auto PlayerMouseLambda = [&mouseQueue, &reading,
                              &queueMutex](const std::vector<pamsi::Move_t>& allMoves) {
        return pamsi::algorithms::PlayerMouse(allMoves, mouseQueue, reading, queueMutex);
    };

    std::thread sfmlLoop(pamsi::sfmlLoop, std::ref(board), std::ref(mouseQueue), std::ref(reading),
                         std::ref(queueMutex));

    std::thread realGame(pamsi::Game, std::ref(board), PlayerMouseLambda,
                         pamsi::algorithms::Random);

    sfmlLoop.join();
    // realGame.join();

    return 0;
}
