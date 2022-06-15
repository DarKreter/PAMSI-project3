#include "Algorithms.hpp"
#include "Board.hpp"
#include <iostream>
#include <iterator>
#include <queue>
#include <random>
#include <vector>

namespace pamsi::algorithms {

pamsi::Move_t Random(const std::vector<pamsi::Move_t>& allMoves, [[maybe_unused]] pamsi::Team_e a,
                     [[maybe_unused]] pamsi::Board_t& board)
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

std::vector<std::pair<pamsi::Board_t, pamsi::Move_t>>
GetAllChildrenOfBoard(pamsi::Board_t& father, Team_e whoseTurn, Move_t firstMoveInSequence,
                      bool figureTaken, std::shared_ptr<Figure_t> lastMovedFigure)
{
    std::vector<std::pair<pamsi::Board_t, pamsi::Move_t>> childrens;
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

            std::vector<std::pair<pamsi::Board_t, pamsi::Move_t>> secondChildrens =
                GetAllChildrenOfBoard(
                    temp, whoseTurn,
                    (firstMoveInSequence.GetSource().x == INT_MAX ? move : firstMoveInSequence),
                    true, temp(move.GetDestination().x, move.GetDestination().y).GetFigure());
            if(secondChildrens.empty()) {
                if(firstMoveInSequence.GetSource().x == INT_MAX)
                    childrens.emplace_back(std::make_pair(temp, move));
                else
                    childrens.emplace_back(std::make_pair(temp, firstMoveInSequence));
            }
            else
                childrens.insert(childrens.end(), secondChildrens.begin(), secondChildrens.end());
        }
        else {
            if(firstMoveInSequence.GetSource().x == INT_MAX)
                childrens.emplace_back(std::make_pair(temp, move));
            else
                childrens.emplace_back(std::make_pair(temp, firstMoveInSequence));
        }
    }

    return childrens;
}

std::pair<int, Move_t*> MinMax(Board_t board, size_t depth, int alpha, int beta, Team_e whoseTurn,
                               Team_e maximizingPlayer, int (*RateBoard)(const Board_t&, Team_e),
                               bool firstOne)
{
    if(depth == 0 || board.CheckLoseConditions(whoseTurn))
        return {RateBoard(board, maximizingPlayer), nullptr};

    if(maximizingPlayer == whoseTurn) {
        int max = INT_MIN;
        size_t count = 0;
        std::vector<int> toChoose;
        auto childrens = GetAllChildrenOfBoard(board, whoseTurn, Move_t());
        for(auto& [child, childMove] : childrens) {
            int eval = MinMax(child, depth - 1, alpha, beta,
                              (whoseTurn == Team_e::white ? Team_e::black : Team_e::white),
                              maximizingPlayer, RateBoard, false)
                           .first;
            if(eval > max) {
                toChoose.clear();
                max = eval;
                toChoose.emplace_back(count);
            }
            else if(eval == max)
                toChoose.emplace_back(count);
            max = std::max(max, eval);
            alpha = std::max(alpha, eval);
            count++;
            if(beta <= alpha)
                break;
        }
        if(firstOne) {
            int which = *select_randomly(toChoose.begin(), toChoose.end());
            return {max, new Move_t(childrens[which].second)};
        }

        return {max, nullptr};
    }
    else {
        int min = INT_MAX;
        size_t count = 0;
        std::vector<int> toChoose;
        auto childrens = GetAllChildrenOfBoard(board, whoseTurn, Move_t());
        for(auto& [child, childMove] : childrens) {
            int eval = MinMax(child, depth - 1, alpha, beta,
                              (whoseTurn == Team_e::white ? Team_e::black : Team_e::white),
                              maximizingPlayer, RateBoard, false)
                           .first;
            if(eval < min) {
                toChoose.clear();
                min = eval;
                toChoose.emplace_back(count);
            }
            else if(eval == min)
                toChoose.emplace_back(count);
            beta = std::min(beta, eval);
            count++;
            if(beta <= alpha)
                break;
        }
        if(firstOne) {
            int which = *select_randomly(toChoose.begin(), toChoose.end());
            return {min, new Move_t(childrens[which].second)};
        }

        return {min, nullptr};
    }
    return {INT_MAX, nullptr};
}

namespace BR {
int CountFigures(const Board_t& board, Team_e who)
{
    if(who == Team_e::white)
        return board.GetWhiteFigures().size() - board.GetBlackFigures().size();
    else
        return board.GetBlackFigures().size() - board.GetWhiteFigures().size();
}
} // namespace BR

} // namespace pamsi::algorithms
