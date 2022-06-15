#ifndef PIECE_PAMSI_PROJECT_DEFINE_H
#define PIECE_PAMSI_PROJECT_DEFINE_H

#include "figure.hpp"

namespace pamsi {

/**
 * @brief Class representing single Piece on the board. It can move one tile per slant.
 *
 */
class Piece_t : public pamsi::Figure_t {

public:
    Piece_t(float radius) : Figure_t(radius, Figure_t::WhoAmI::Piece){};
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

#endif // PIECE_PAMSI_PROJECT_DEFINE_H