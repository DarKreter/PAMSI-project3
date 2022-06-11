#ifndef GAME_PAMSI_PROJECT_DEFINE_H
#define GAME_PAMSI_PROJECT_DEFINE_H

#include "board.hpp"
#include <mutex>

namespace pamsi {

void Game(pamsi::Board_t& board, std::mutex& mtx);
void sfmlLoop(pamsi::Board_t& board, std::mutex& mtx);
Move_t GetValidMoveFromPlayer(std::vector<Move_t>& allMoves);
} // namespace pamsi

#endif // GAME_PAMSI_PROJECT_DEFINE_H