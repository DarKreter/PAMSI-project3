#include "pawn.hpp"
#include "board.hpp"
#include <initializer_list>
#include <iostream>

namespace pamsi {

std::vector<sf::Vector2i> Pawn_t::GetPossibleMoves()
{
    auto options = {sf::Vector2i(-1, -1), sf::Vector2i(1, -1)};

    std::vector<sf::Vector2i> moves;

    for(auto& option : options) {
        try {
            if((*_myBoard)(_coord.x + option.x, _coord.y + option.y).GetFigure() == nullptr)
                moves.emplace_back(sf::Vector2i(_coord.x + option.x, _coord.y + option.y));
        }
        catch(std::out_of_range& e) {
            continue;
        }
    }

    return moves;
}

} // namespace pamsi
