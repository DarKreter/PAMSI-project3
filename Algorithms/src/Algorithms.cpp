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
    // Just random shot
    return *select_randomly(allMoves.begin(), allMoves.end());
}

pamsi::Move_t LastAvailableMove(const std::vector<pamsi::Move_t>& allMoves)
{
    // always last from container
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
    // lambda expression that gets pressed tile (tries until it happen)
    auto GetElFromQueue = [&]() {
        while(true) {
            queueMutex.lock();
            if(!mouseQueue.empty())
                break;
            queueMutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        // get new pressed tile
        auto pressedTile = mouseQueue.back();
        // remove it from queue
        mouseQueue.pop();
        // std::cout << pressedTile.x << ", " << pressedTile.y << std::endl;

        queueMutex.unlock();
        return pressedTile;
    };

    Move_t myMove(source, dest);
    do {
        // Get two tiles
        source = GetElFromQueue();
        dest = GetElFromQueue();
        // Set them to source and destination
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
    // if figure wasnt taken get all possible moves for board and team
    if(!figureTaken)
        allMoves = std::move(father.GetAllPossibleMoves(whoseTurn, figureTaken));
    else {
        // get lastMovedFigure coord and get this figure address
        auto trulyLastMovedFigure =
            father(lastMovedFigure->GetCoordinates().x, lastMovedFigure->GetCoordinates().y)
                .GetFigure();
        // Check attack position for it
        allMoves = std::move(trulyLastMovedFigure->GetAttackMoves());
    }
    // Go through all moves
    for(Move_t& move : allMoves) {
        father.lock();
        Board_t temp = father; // copy board
        temp.MoveFigure(move);
        father.unlock();

        if(move.GetTaken() != nullptr) { // if it was strike
            // Get grandchildrens with proper parameters
            std::vector<std::pair<pamsi::Board_t, pamsi::Move_t>> secondChildrens =
                GetAllChildrenOfBoard(
                    temp, whoseTurn,
                    (firstMoveInSequence.GetSource().x == INT_MAX ? move : firstMoveInSequence),
                    true, temp(move.GetDestination().x, move.GetDestination().y).GetFigure());
            if(secondChildrens.empty()) { // if empty
                if(firstMoveInSequence.GetSource().x == INT_MAX)
                    childrens.emplace_back(std::make_pair(temp, move)); // add last move
                else
                    childrens.emplace_back(std::make_pair(temp, firstMoveInSequence));
            }
            else // if not empty
                childrens.insert(childrens.end(), secondChildrens.begin(),
                                 secondChildrens.end()); // append grandchildrens
        }
        else { // if it was normal move
            if(firstMoveInSequence.GetSource().x == INT_MAX)
                childrens.emplace_back(
                    std::make_pair(temp, move)); // insert this move into children container
            else
                childrens.emplace_back(std::make_pair(
                    temp, firstMoveInSequence)); // if its last in sequence them add the first one
        }
    }

    return childrens;
}

std::pair<int, Move_t*> MinMax(Board_t board, size_t depth, int alpha, int beta, Team_e whoseTurn,
                               Team_e maximizingPlayer, int (*RateBoard)(const Board_t&, Team_e),
                               bool firstOne)
{
    // if we reach desired depth or its end of game just rate the board
    if(depth == 0 || board.CheckLoseConditions(whoseTurn))
        return {RateBoard(board, maximizingPlayer), nullptr};

    // if its turn player we maximize
    if(maximizingPlayer == whoseTurn) {
        int max = INT_MIN;
        size_t count = 0;
        std::vector<int> toChoose;
        auto childrens = GetAllChildrenOfBoard(board, whoseTurn, Move_t()); // Get all childerns
        // go through all of them
        for(auto& [child, childMove] : childrens) {
            // recursion with minmax
            int eval = MinMax(child, depth - 1, alpha, beta,
                              (whoseTurn == Team_e::white ? Team_e::black : Team_e::white),
                              maximizingPlayer, RateBoard, false)
                           .first;
            if(eval > max) {      // if its bigger
                toChoose.clear(); // clear current moves
                max = eval;       // get new max value
                toChoose.emplace_back(count);
            }
            else if(eval == max)              // if equal to current max
                toChoose.emplace_back(count); // append this move
            max = std::max(max, eval);
            alpha = std::max(alpha, eval);
            count++;
            if(beta <= alpha) // alpha beta pruning
                break;
        }
        if(firstOne) {
            // Chose random move from all with max value
            int which = *select_randomly(toChoose.begin(), toChoose.end());
            return {max, new Move_t(childrens[which].second)};
        }

        return {max, nullptr};
    }
    // same with min
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
    // just calculate difference
    if(who == Team_e::white)
        return board.GetWhiteFigures().size() - board.GetBlackFigures().size();
    else
        return board.GetBlackFigures().size() - board.GetWhiteFigures().size();
}

int CountFiguresWithKing(const Board_t& board, Team_e who)
{
    int whiteSum = 0, blackSum = 0;
    // calculate difference, but with counting king as 4 pieces
    for(auto& figure : board.GetWhiteFigures())
        switch(figure->GetWhoAmI()) {
        case Figure_t::WhoAmI::Piece:
            whiteSum++;
            break;
        case Figure_t::WhoAmI::King:
            whiteSum += 4;
            break;
        default:
            break;
        }

    for(auto& figure : board.GetBlackFigures())
        switch(figure->GetWhoAmI()) {
        case Figure_t::WhoAmI::Piece:
            blackSum++;
            break;
        case Figure_t::WhoAmI::King:
            blackSum += 4;
            break;
        default:
            break;
        }

    if(who == Team_e::white)
        return whiteSum - blackSum;
    else
        return blackSum - whiteSum;
}

int ValuePosition(const Board_t& board, Team_e who)
{
    // Same as `CountFiguresWithKing`, but add value to pieces if they are closer to became king
    int whiteSum = 0, blackSum = 0;
    int temp;
    for(auto& figure : board.GetWhiteFigures())
        switch(figure->GetWhoAmI()) {
        case Figure_t::WhoAmI::Piece:
            temp = std::abs(8l - figure->GetCoordinates().y);
            whiteSum += temp;
            break;
        case Figure_t::WhoAmI::King:
            whiteSum += 12;
            break;
        default:
            break;
        }

    for(auto& figure : board.GetBlackFigures())
        switch(figure->GetWhoAmI()) {
        case Figure_t::WhoAmI::Piece:
            temp = figure->GetCoordinates().y;
            blackSum += temp;
            break;
        case Figure_t::WhoAmI::King:
            blackSum += 12;
            break;
        default:
            break;
        }

    if(who == Team_e::white)
        return whiteSum - blackSum;
    else
        return blackSum - whiteSum;
}
} // namespace BR

} // namespace pamsi::algorithms
