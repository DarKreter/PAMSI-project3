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

/**
 * @brief Choose random move from available
 *
 * @param allMoves list of all moves
 * @param a unused
 * @param board unused
 * @return Move_t chosen move
 */
Move_t Random(const std::vector<Move_t>& allMoves, [[maybe_unused]] pamsi::Team_e a,
              [[maybe_unused]] pamsi::Board_t& board);

/**
 * @brief Choose last available move from vector
 *
 * @param allMoves list of all moves
 * @return Move_t chosen move
 */
Move_t LastAvailableMove(const std::vector<Move_t>& allMoves);

/**
 * @brief Allow player to move chosen figure. Option is read from stdin
 *
 * @param allMoves list of all moves
 * @return Move_t chosen move
 */
Move_t PlayerConsole(const std::vector<Move_t>& allMoves);

/**
 * @brief Allow player to move chosen figure. Player choose option clicking on the board.
 *
 * @param allMoves list of all moves
 * @param mouseQueue queue with pressed pixels
 * @param reading enables another thread to keep checking mouse
 * @param queueMutex mutex for queue from mouse checking thread
 * @return Move_t Move_t chosen move
 */
Move_t PlayerMouse(const std::vector<Move_t>& allMoves, std::queue<sf::Vector2u>& mouseQueue,
                   bool& reading, std::mutex& queueMutex);

/**
 * @brief Returns all possible variants of board from current board position and knowlegde whose
 * turn is now
 *
 * @param father source board
 * @param whoseTurn whose turn is now
 * @param firstMoveInSequence check if sequence already was started
 * @param figureTaken if figure has been already taken
 * @param lastMovedFigure remember last moves figure
 * @return std::vector<std::pair<pamsi::Board_t, pamsi::Move_t>>
 */
std::vector<std::pair<pamsi::Board_t, pamsi::Move_t>>
GetAllChildrenOfBoard(pamsi::Board_t& father, Team_e whoseTurn, Move_t firstMoveInSequence,
                      bool figureTaken = false,
                      std::shared_ptr<Figure_t> lastMovedFigure = nullptr);

/**
 * @brief Algorithm MinMax that choose best possible move with provided board rating function and
 * provided depth. It also uses alpha beta pruning
 *
 *
 * @param board current board
 * @param depth MinMax depth
 * @param alpha for alpha beta pruning
 * @param beta for alpha beta pruning
 * @param whoseTurn whose turn is now
 * @param maximizingPlayer which player we prioritize
 * @param RateBoard function that rates board
 * @param firstOne if its first call of MinMax
 * @return std::pair<int, Move_t*> returns value of best move
 */
std::pair<int, Move_t*> MinMax(Board_t board, size_t depth, int alpha, int beta, Team_e whoseTurn,
                               Team_e maximizingPlayer,
                               int (*RateBoard)(const Board_t& board, Team_e),
                               bool firstOne = true);

namespace BR {
/**
 * @brief Rates the board with counting white and black figures
 */
int CountFigures(const Board_t& board, Team_e who);
/**
 * @brief Rates the board with counting white and black figures, but king gots more points
 */
int CountFiguresWithKing(const Board_t& board, Team_e who);
/**
 * @brief Rates the board with counting white and black figures, with prioritizing pieces closer to
 * becoming king
 */
int ValuePosition(const Board_t& board, Team_e who);
} // namespace BR

} // namespace pamsi::algorithms

#endif // ALGORITHMS_PAMSI_PROJECT_DEFINE_H