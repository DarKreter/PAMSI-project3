#ifndef KING_PAMSI_PROJECT_DEFINE_H
#define KING_PAMSI_PROJECT_DEFINE_H

#include "figure.hpp"

namespace pamsi {

class King_t : public pamsi::Figure_t {

public:
    King_t(float radius) : Figure_t(radius, Figure_t::WhoAmI::King){};

    std::vector<pamsi::Move_t> GetNormalMoves() override;
    std::vector<pamsi::Move_t> GetAttackMoves() override;
};

} // namespace pamsi

#endif // KING_PAMSI_PROJECT_DEFINE_H