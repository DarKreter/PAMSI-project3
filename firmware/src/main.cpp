#include "Algorithms.hpp"
#include "board.hpp"
#include "game.hpp"
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

constexpr size_t windowsSize = 1000;
constexpr size_t borderWidth = 5.f;

int main()
{
    pamsi::Board_t board(windowsSize, borderWidth);

    pamsi::Board_t dupa = board;
    // dupa(1,1)
    dupa._blackFigures.erase(
        std::remove(dupa._blackFigures.begin(), dupa._blackFigures.end(), dupa(1, 0).GetFigure()),
        dupa._blackFigures.end());

    board = dupa;

    std::queue<sf::Vector2u> mouseQueue;
    bool reading = false;
    std::mutex mtx, queueMutex;

    auto PlayerMouseLambda = [&mouseQueue, &reading,
                              &queueMutex](const std::vector<pamsi::Move_t>& allMoves) {
        return pamsi::algorithms::PlayerMouse(allMoves, mouseQueue, reading, queueMutex);
    };

    std::thread sfmlLoop(pamsi::sfmlLoop, std::ref(board), std::ref(mtx), std::ref(mouseQueue),
                         std::ref(reading), std::ref(queueMutex));

    std::thread realGame(pamsi::Game, std::ref(board), std::ref(mtx), PlayerMouseLambda,
                         pamsi::algorithms::Random);

    sfmlLoop.join();
    // realGame.join();

    return 0;
}
