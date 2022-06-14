#include "Algorithms.hpp"
#include "Board.hpp"
#include <iostream>
#include <iterator>
#include <queue>
#include <random>
#include <vector>

namespace pamsi::algorithms {

// playerMove = GetValidMoveFromPlayer(allMoves);

pamsi::Move_t Random(const std::vector<pamsi::Move_t>& allMoves)
{
    return *select_randomly(allMoves.begin(), allMoves.end());
}

pamsi::Move_t LastAvailableMove(const std::vector<pamsi::Move_t>& allMoves)
{
    return *(std::end(allMoves) - 1);
}

Move_t PlayerConsole(const std::vector<Move_t>& allMoves)
{
    sf::Vector2u source, dest;
    std::vector<Move_t>::const_iterator result;
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

Move_t PlayerMouse([[maybe_unused]] const std::vector<pamsi::Move_t>& allMoves,
                   std::queue<sf::Vector2u>& mouseQueue, bool& reading, std::mutex& queueMutex)
{
    reading = true;
    sf::Vector2u source, dest;
    std::vector<Move_t>::const_iterator result;
    auto GetElFromQueue = [&]() {
        while(true) {
            queueMutex.lock();
            if(!mouseQueue.empty())
                break;
            queueMutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        auto pressedTile = mouseQueue.back();
        mouseQueue.pop();
        // std::cout << pressedTile.x << ", " << pressedTile.y << std::endl;

        queueMutex.unlock();
        return pressedTile;
    };

    Move_t myMove(source, dest);
    do {
        source = GetElFromQueue();
        dest = GetElFromQueue();

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

    reading = false;
    return *result;
}

std::vector<pamsi::Board_t> GetAllChildrenOfBoard(const pamsi::Board_t& father)
{
    std::vector<pamsi::Board_t> childrens;
    Board_t dupa = father;
    // dupa(1,1)
    dupa._blackFigures.erase(
        std::remove(dupa._blackFigures.begin(), dupa._blackFigures.end(), dupa(1, 0).GetFigure()),
        dupa._blackFigures.end());

    childrens.emplace_back(dupa);

    dupa = father;
    // dupa(1,1)
    dupa._blackFigures.erase(
        std::remove(dupa._blackFigures.begin(), dupa._blackFigures.end(), dupa(3, 0).GetFigure()),
        dupa._blackFigures.end());

    childrens.emplace_back(dupa);

    return childrens;
}

} // namespace pamsi::algorithms
