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

Move_t Random(const std::vector<Move_t>& allMoves);

Move_t LastAvailableMove(const std::vector<Move_t>& allMoves);

Move_t PlayerConsole(const std::vector<Move_t>& allMoves);

Move_t PlayerMouse(const std::vector<Move_t>& allMoves, std::queue<sf::Vector2u>& mouseQueue,
                   bool& reading, std::mutex& queueMutex);

std::vector<pamsi::Board_t>
GetAllChildrenOfBoard(pamsi::Board_t& father, Team_e whoseTurn, bool figureTaken = false,
                      std::shared_ptr<Figure_t> lastMovedFigure = nullptr);

int MinMax(Board_t board, size_t depth, int alpha, int beta, Team_e whoseTurn,
           Team_e maximizingPlayer);

namespace BR {
int CountFigures(const Board_t& board);
}

} // namespace pamsi::algorithms

#endif // ALGORITHMS_PAMSI_PROJECT_DEFINE_H