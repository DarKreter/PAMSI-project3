#ifndef GAME_PAMSI_PROJECT_DEFINE_H
#define GAME_PAMSI_PROJECT_DEFINE_H

#include "board.hpp"
#include <mutex>

namespace pamsi {

void Game(pamsi::Board_t& board, std::mutex& mtx,
          std::function<pamsi::Move_t(std::vector<Move_t>)> whiteMove,
          std::function<pamsi::Move_t(std::vector<Move_t>)> blackMove);
void sfmlLoop(pamsi::Board_t& board, std::mutex& mtx, std::queue<sf::Vector2u>& mouseQueue,
              bool& reading, std::mutex& queueMutex);

} // namespace pamsi

#endif // GAME_PAMSI_PROJECT_DEFINE_H