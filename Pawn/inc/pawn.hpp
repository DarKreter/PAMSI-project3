#ifndef PAWN_PAMSI_PROJECT_DEFINE_H
#define PAWN_PAMSI_PROJECT_DEFINE_H

#include "figure.hpp"

namespace pamsi {

class Pawn_t : public pamsi::Figure_t {

public:
    Pawn_t(float radius) : Figure_t(radius){};

    std::vector<pamsi::Move_t> GetNormalMoves() override;
    std::vector<pamsi::Move_t> GetAttackMoves() override;
};

} // namespace pamsi

#endif // PAWN_PAMSI_PROJECT_DEFINE_H