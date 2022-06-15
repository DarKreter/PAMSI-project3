#ifndef KING_PAMSI_PROJECT_DEFINE_H
#define KING_PAMSI_PROJECT_DEFINE_H

#include "figure.hpp"

namespace pamsi {

/**
 * @brief class representing king on the board. King can move diagonally without limits.
 *
 */
class King_t : public pamsi::Figure_t {

public:
    King_t(float radius) : Figure_t(radius, Figure_t::WhoAmI::King){};

    /**
     * @brief overrided method from Figure_t
     */
    std::vector<pamsi::Move_t> GetNormalMoves() override;
    /**
     * @brief overrided method from Figure_t
     */
    std::vector<pamsi::Move_t> GetAttackMoves() override;
};

} // namespace pamsi

#endif // KING_PAMSI_PROJECT_DEFINE_H