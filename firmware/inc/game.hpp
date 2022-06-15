#ifndef GAME_PAMSI_PROJECT_DEFINE_H
#define GAME_PAMSI_PROJECT_DEFINE_H

#include "board.hpp"
#include <mutex>

namespace pamsi {

typedef std::function<pamsi::Move_t(std::vector<Move_t>, pamsi::Team_e, pamsi::Board_t&)> function;

/**
 * @brief game handling thread
 *
 * @param board board to play on
 * @param whiteMove white team will move with this function
 * @param blackMove black team will move with this function
 */
void Game(pamsi::Board_t& board, function whiteMove, function blackMove);
/**
 * @brief SFML and event handling thread
 *
 * @param board board to draw
 * @param mouseQueue queue to pass pressed by mouse pixels
 * @param reading flag that enables checking mouse pressed pixels
 * @param queueMutex mutex for mouseQueue
 */
void sfmlLoop(pamsi::Board_t& board, std::queue<sf::Vector2u>& mouseQueue, bool& reading,
              std::mutex& queueMutex);

} // namespace pamsi

#endif // GAME_PAMSI_PROJECT_DEFINE_H