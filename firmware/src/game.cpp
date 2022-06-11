#include "game.hpp"
#include "move.hpp"
#include <chrono>
#include <iostream>
#include <thread>

#include <iterator>
#include <random>

template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g)
{
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template <typename Iter>
Iter select_randomly(Iter start, Iter end)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

namespace pamsi {
void Game(pamsi::Board_t& board, std::mutex& mtx)
{
    // white always starts
    pamsi::Team_e whoseTurn = pamsi::Team_e::white;
    bool figureTaken = false;

    getchar();
    while(true) {

        // Check lose conditions
        if(!figureTaken && board.CheckLoseConditions(whoseTurn)) {
            std::cout << "GAME OVER!" << std::endl;
            if(whoseTurn == pamsi::Team_e::white)
                std::cout << "BLACK WON!" << std::endl;
            else if(whoseTurn == pamsi::Team_e::black)
                std::cout << "WHITE WON!" << std::endl;
            getchar();
            exit(0);
        }

        // Get all possible moves for current player
        auto allMoves = std::move(board.GetAllPossibleMoves(whoseTurn, figureTaken));

        // DEBUG
        // for(auto& move : allMoves) {
        //     std::cout << move.GetSource().x << " " << move.GetSource().y << "\t"
        //               << move.GetDestination().x << " " << move.GetDestination().y << "\t"
        //               << move.GetTaken() << std::endl;
        // }
        // std::cout << std::endl;
        // If there is no moves for player and he didn't do any move already
        if(!figureTaken && allMoves.empty()) {
            std::cout << "DRAW!" << std::endl;
            std::cout << "GAME OVER!" << std::endl;
            getchar();
            exit(0);
        }
        // He don't have moves but already make some
        else if(figureTaken && allMoves.empty()) {
            figureTaken = false;
        }
        // He has move
        else {
            // Get valid move from player
            // Move_t playerMove = GetValidMoveFromPlayer(allMoves);
            Move_t playerMove = *(std::end(allMoves) - 1);
            // Move_t playerMove = *select_randomly(allMoves.begin(), allMoves.end());
            getchar();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            // Move
            mtx.lock();
            board.MoveFigure(playerMove);
            mtx.unlock();

            if(playerMove.GetTaken()) {
                figureTaken = true;
                continue;
            }
            else
                figureTaken = false;
        }

        // Change player
        if(whoseTurn == pamsi::Team_e::white)
            whoseTurn = pamsi::Team_e::black;
        else if(whoseTurn == pamsi::Team_e::black)
            whoseTurn = pamsi::Team_e::white;
    }
}

void NormalMove() {}

Move_t GetValidMoveFromPlayer(std::vector<Move_t>& allMoves)
{
    sf::Vector2u source, dest;
    std::vector<Move_t>::iterator result;
    Move_t myMove(source, dest);
    do {

        // Get move from player
        std::cin >> source.x >> source.y;
        std::cin >> dest.x >> dest.y;

        myMove.SetSource(source);
        myMove.SetDestination(dest);
        // Check if it's valid
        result =
            std::find_if(std::begin(allMoves), std::end(allMoves), [&myMove](auto& currentMove) {
                if(myMove == currentMove)
                    return true;
                return false;
            });

        if(result == std::end(allMoves))
            std::cout << "Invalid move!" << std::endl;

    } while(result == std::end(allMoves));

    std::cout << "Valid move!" << std::endl;

    return *result;
}

constexpr size_t windowsSize = 1000;
constexpr size_t borderWidth = 5.f;

void sfmlLoop(pamsi::Board_t& board, std::mutex& mtx)
{
    sf::RenderWindow window(sf::VideoMode(windowsSize, windowsSize), "Checkers!",
                            sf::Style::Default);

    window.setFramerateLimit(60);

    // run the program as long as the window is open
    while(window.isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        sf::Event event;
        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        mtx.lock();
        window.draw(board);
        mtx.unlock();
        // end the current frame
        window.display();
    }

    exit(0);
}

} // namespace pamsi
