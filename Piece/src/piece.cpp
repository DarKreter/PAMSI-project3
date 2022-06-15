#include "piece.hpp"
#include "board.hpp"
#include <iostream>

namespace pamsi {

std::vector<pamsi::Move_t> Piece_t::GetNormalMoves()
{
    // Get available direction for specified team
    // Piece can only go forward on a slant
    std::vector<sf::Vector2i> options;
    switch(_team) {
    case Team_e::white:
        options.emplace_back(sf::Vector2i(-1, -1));
        options.emplace_back(sf::Vector2i(1, -1));
        break;
    case Team_e::black:
        options.emplace_back(sf::Vector2i(-1, 1));
        options.emplace_back(sf::Vector2i(1, 1));
        break;
    }

    std::vector<pamsi::Move_t> moves;
    // Go through all option
    for(auto& option : options) {
        try {
            // Get figure pointer on destination tile
            auto figure = (*_myBoard)(_coord.x + option.x, _coord.y + option.y).GetFigure();
            // If there is no figure
            if(figure == nullptr)
                // It is possible to go here
                moves.emplace_back(
                    Move_t(_coord, sf::Vector2u(_coord.x + option.x, _coord.y + option.y)));
        }
        // If direction is outside the board
        catch(std::out_of_range& e) {
            continue;
        }
    }
    // Return vector of possible moves
    return moves;
}

std::vector<pamsi::Move_t> Piece_t::GetAttackMoves()
{
    // Get possible options for piece to take someone
    std::vector<sf::Vector2i> options = {sf::Vector2i(-1, -1), sf::Vector2i(1, -1),
                                         sf::Vector2i(-1, 1), sf::Vector2i(1, 1)};
    std::vector<pamsi::Move_t> moves;
    // Get through all options
    for(auto& option : options) {
        try {
            // Get figure on attacked tile
            std::shared_ptr<Figure_t> figure =
                (*_myBoard)(_coord.x + option.x, _coord.y + option.y).GetFigure();
            // If there is someone and is from opponents team
            if(figure != nullptr && figure->GetTeam() != _team) {
                // Get figure on tile after opponent
                auto a = (*_myBoard)(_coord.x + 2 * option.x, _coord.y + 2 * option.y).GetFigure();
                // If nobody is here
                if(!a) {
                    // It is possible move, with figure as taken guy
                    moves.emplace_back(Move_t(
                        _coord, sf::Vector2u(_coord.x + 2 * option.x, _coord.y + 2 * option.y),
                        figure));
                }
            }
        }
        // If direction is outside the board
        catch(std::out_of_range& e) {
            continue;
        }
    }
    // Return vector of possible moves
    return moves;
}

} // namespace pamsi
