#include "Algorithms.hpp"
#include "board.hpp"
#include "figure.hpp"
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
                              &queueMutex](const std::vector<pamsi::Move_t>& allMoves,
                                           [[maybe_unused]] pamsi::Team_e a,
                                           [[maybe_unused]] pamsi::Board_t& board) {
        return pamsi::algorithms::PlayerMouse(allMoves, mouseQueue, reading, queueMutex);
    };

    int depth = 3;
    auto RateBoard = pamsi::algorithms::BR::CountFiguresWithKing;

    auto MinMax_1 = [depth, RateBoard]([[maybe_unused]] const std::vector<pamsi::Move_t>& allMoves,
                                       pamsi::Team_e whoseTurn, pamsi::Board_t& board) {
        pamsi::Move_t* minmax = pamsi::algorithms::MinMax(board, depth, INT_MIN, INT_MAX, whoseTurn,
                                                          whoseTurn, RateBoard)
                                    .second;
        pamsi::Move_t playerMove = *minmax;
        delete minmax;
        return playerMove;
    };
    // depth = 3;
    // RateBoard = pamsi::algorithms::BR::ValuePosition;
    // auto MinMax_2 = [depth, RateBoard]([[maybe_unused]] const std::vector<pamsi::Move_t>&
    // allMoves,
    //                                    pamsi::Team_e whoseTurn, pamsi::Board_t& board) {
    //     pamsi::Move_t* minmax = pamsi::algorithms::MinMax(board, depth, INT_MIN, INT_MAX,
    //     whoseTurn,
    //                                                       whoseTurn, RateBoard)
    //                                 .second;
    //     pamsi::Move_t playerMove = *minmax;
    //     delete minmax;
    //     return playerMove;
    // };

    std::thread sfmlLoop(pamsi::sfmlLoop, std::ref(board), std::ref(mouseQueue), std::ref(reading),
                         std::ref(queueMutex));

    std::thread realGame(pamsi::Game, std::ref(board), PlayerMouseLambda, MinMax_1);

    sfmlLoop.join();
    realGame.join();

    return 0;
}
