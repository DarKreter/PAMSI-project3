#include "pawn.hpp"
#include <initializer_list>
#include <iostream>

namespace pamsi {

std::list<sf::Vector2u> Pawn_t::GetPossibleMoves()
{
    std::cout << _coord.x << " " << _coord.y << ":" << std::endl;

    auto options = {sf::Vector2u(-1, 1), sf::Vector2u(1, 1)};

    for(auto& option : options) {
        // Check on the board if new position is empty
        // Pointer to board is needed
        // Also tile need to know if something is on him (pointer)
    }

    return std::list<sf::Vector2u>();
}

} // namespace pamsi
