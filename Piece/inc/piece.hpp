#ifndef PIECE_PAMSI_PROJECT_DEFINE_H
#define PIECE_PAMSI_PROJECT_DEFINE_H

#include "figure.hpp"

namespace pamsi {

class Piece_t : public pamsi::Figure_t {

public:
    Piece_t(float radius) : Figure_t(radius){};

    std::vector<pamsi::Move_t> GetNormalMoves() override;
    std::vector<pamsi::Move_t> GetAttackMoves() override;
};

} // namespace pamsi

#endif // PIECE_PAMSI_PROJECT_DEFINE_H