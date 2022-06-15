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
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return *select_randomly(allMoves.begin(), allMoves.end());
}

pamsi::Move_t LastAvailableMove(const std::vector<pamsi::Move_t>& allMoves)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

std::vector<pamsi::Board_t> GetAllChildrenOfBoard(pamsi::Board_t& father, Team_e whoseTurn,
                                                  bool figureTaken,
                                                  std::shared_ptr<Figure_t> lastMovedFigure)
{
    std::vector<pamsi::Board_t> childrens;
    // Get all possible moves for current player
    std::vector<Move_t> allMoves;
    if(!figureTaken)
        allMoves = std::move(father.GetAllPossibleMoves(whoseTurn, figureTaken));
    else {
        auto trulyLastMovedFigure =
            father(lastMovedFigure->GetCoordinates().x, lastMovedFigure->GetCoordinates().y)
                .GetFigure();

        allMoves = std::move(trulyLastMovedFigure->GetAttackMoves());
    }
    for(Move_t& move : allMoves) {
        father.lock();
        Board_t temp = father;
        temp.MoveFigure(move);
        father.unlock();

        if(move.GetTaken() != nullptr) {
            std::vector<pamsi::Board_t> secondChildrens = GetAllChildrenOfBoard(
                temp, whoseTurn, true,
                temp(move.GetDestination().x, move.GetDestination().y).GetFigure());
            if(secondChildrens.empty())
                childrens.emplace_back(temp);
            else
                childrens.insert(childrens.end(), secondChildrens.begin(), secondChildrens.end());
        }
        else
            childrens.emplace_back(temp);
    }

    return childrens;
}

int MinMax(Board_t board, size_t depth, int alpha, int beta, Team_e whoseTurn,
           Team_e maximizingPlayer)
{
    if(depth == 0 || board.CheckLoseConditions(whoseTurn))
        return BR::CountFigures(board);

    if(maximizingPlayer == whoseTurn) {
        int max = INT_MIN;
        auto childrens = GetAllChildrenOfBoard(board, whoseTurn);
        for(auto& child : childrens) {
            int eval = MinMax(child, depth - 1, alpha, beta,
                              (whoseTurn == Team_e::white ? Team_e::black : Team_e::white),
                              maximizingPlayer);
            max = std::max(max, eval);
            alpha = std::max(alpha, eval);
            if(beta <= alpha)
                break;
        }
        return max;
    }
    else {
        int min = INT_MAX;
        auto childrens = GetAllChildrenOfBoard(board, whoseTurn);
        for(auto& child : childrens) {
            int eval = MinMax(child, depth - 1, alpha, beta,
                              (whoseTurn == Team_e::white ? Team_e::black : Team_e::white),
                              maximizingPlayer);
            min = std::min(min, eval);
            beta = std::min(beta, eval);
            if(beta <= alpha)
                break;
        }
        return min;
    }
    return INT_MAX;
}

namespace BR {
int CountFigures(const Board_t& board)
{
    return board.GetWhiteFigures().size() - board.GetBlackFigures().size();
}
} // namespace BR

} // namespace pamsi::algorithms
