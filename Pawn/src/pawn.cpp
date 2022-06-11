#include "pawn.hpp"
#include "board.hpp"
#include <iostream>

namespace pamsi {

std::vector<pamsi::Move_t> Pawn_t::GetNormalMoves()
{
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

    for(auto& option : options) {
        try {
            if((*_myBoard)(_coord.x + option.x, _coord.y + option.y).GetFigure() == nullptr)
                moves.emplace_back(
                    Move_t(_coord, sf::Vector2u(_coord.x + option.x, _coord.y + option.y)));
        }
        catch(std::out_of_range& e) {
            continue;
        }
    }

    return moves;
}

std::vector<pamsi::Move_t> Pawn_t::GetAttackMoves()
{
    std::vector<sf::Vector2i> options = {sf::Vector2i(-1, -1), sf::Vector2i(1, -1),
                                         sf::Vector2i(-1, 1), sf::Vector2i(1, 1)};
    std::vector<pamsi::Move_t> moves;

    for(auto& option : options) {
        try {
            std::shared_ptr<Figure_t> figure =
                (*_myBoard)(_coord.x + option.x, _coord.y + option.y).GetFigure();
            // There is someone and is from opponents team
            if(figure != nullptr && figure->GetTeam() != _team) {
                auto a = (*_myBoard)(_coord.x + 2 * option.x, _coord.y + 2 * option.y).GetFigure();
                if(!a) {
                    moves.emplace_back(Move_t(
                        _coord, sf::Vector2u(_coord.x + 2 * option.x, _coord.y + 2 * option.y),
                        figure));
                }
            }
        }
        catch(std::out_of_range& e) {
            continue;
        }
    }

    return moves;
}

} // namespace pamsi
