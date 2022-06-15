#ifndef GAME_PAMSI_PROJECT_DEFINE_H
#define GAME_PAMSI_PROJECT_DEFINE_H

#include "board.hpp"
#include <mutex>

namespace pamsi {

typedef std::function<pamsi::Move_t(std::vector<Move_t>, pamsi::Team_e, pamsi::Board_t&)> function;

void Game(pamsi::Board_t& board, function whiteMove, function blackMove);
void sfmlLoop(pamsi::Board_t& board, std::queue<sf::Vector2u>& mouseQueue, bool& reading,
              std::mutex& queueMutex);

} // namespace pamsi

#endif // GAME_PAMSI_PROJECT_DEFINE_H