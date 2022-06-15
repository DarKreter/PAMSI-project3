#ifndef ALGORITHMS_PAMSI_PROJECT_DEFINE_H
#define ALGORITHMS_PAMSI_PROJECT_DEFINE_H

#include "board.hpp"
#include "move.hpp"

namespace pamsi::algorithms {

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

Move_t Random(const std::vector<Move_t>& allMoves, [[maybe_unused]] pamsi::Team_e a,
              [[maybe_unused]] pamsi::Board_t& board);

Move_t LastAvailableMove(const std::vector<Move_t>& allMoves);

Move_t PlayerConsole(const std::vector<Move_t>& allMoves);

Move_t PlayerMouse(const std::vector<Move_t>& allMoves, std::queue<sf::Vector2u>& mouseQueue,
                   bool& reading, std::mutex& queueMutex);

std::vector<std::pair<pamsi::Board_t, pamsi::Move_t>>
GetAllChildrenOfBoard(pamsi::Board_t& father, Team_e whoseTurn, Move_t firstMoveInSequence,
                      bool figureTaken = false,
                      std::shared_ptr<Figure_t> lastMovedFigure = nullptr);

std::pair<int, Move_t*> MinMax(Board_t board, size_t depth, int alpha, int beta, Team_e whoseTurn,
                               Team_e maximizingPlayer,
                               int (*RateBoard)(const Board_t& board, Team_e),
                               bool firstOne = true);

namespace BR {
int CountFigures(const Board_t& board, Team_e who);
}

} // namespace pamsi::algorithms

#endif // ALGORITHMS_PAMSI_PROJECT_DEFINE_H