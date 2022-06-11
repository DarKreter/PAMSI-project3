#ifndef GAME_PAMSI_PROJECT_DEFINE_H
#define GAME_PAMSI_PROJECT_DEFINE_H

#include "board.hpp"
namespace pamsi {

void Game(pamsi::Board_t& board);
void sfmlLoop(pamsi::Board_t& board);
Move_t GetValidMoveFromPlayer(std::vector<Move_t>& allMoves);
} // namespace pamsi

#endif // GAME_PAMSI_PROJECT_DEFINE_H