#include "king.hpp"
#include "board.hpp"
#include <iostream>

namespace pamsi {

std::vector<pamsi::Move_t> King_t::GetNormalMoves()
{
    // Get possible options for piece to take someone
    std::vector<sf::Vector2i> options = {sf::Vector2i(-1, -1), sf::Vector2i(1, -1),
                                         sf::Vector2i(-1, 1), sf::Vector2i(1, 1)};

    std::vector<pamsi::Move_t> moves;
    std::shared_ptr<Figure_t> figure = nullptr;
    // Go through all option
    for(auto& option : options) {
        try {
            auto backupOption = option;
            while(figure == nullptr) {
                figure = (*_myBoard)(_coord.x + option.x, _coord.y + option.y).GetFigure();
                if(figure == nullptr) {
                    moves.emplace_back(
                        Move_t(_coord, sf::Vector2u(_coord.x + option.x, _coord.y + option.y)));
                    option += backupOption;
                }
            }
            figure = nullptr;
        }
        // If direction is outside the board
        catch(std::out_of_range& e) {
            figure = nullptr;
            continue;
        }
    }
    // Return vector of possible moves
    return moves;
}

std::vector<pamsi::Move_t> King_t::GetAttackMoves()
{
    // Get possible options for piece to take someone
    std::vector<sf::Vector2i> options = {sf::Vector2i(-1, -1), sf::Vector2i(1, -1),
                                         sf::Vector2i(-1, 1), sf::Vector2i(1, 1)};

    std::vector<pamsi::Move_t> moves;
    std::shared_ptr<Figure_t> figure = nullptr;
    // Go through all option
    for(auto& option : options) {
        try {
            auto backupOption = option;
            while(figure == nullptr) {
                figure = (*_myBoard)(_coord.x + option.x, _coord.y + option.y).GetFigure();
                option += backupOption;
            }
            // If its from my team, then no strikes this way
            if(figure->GetTeam() == _team)
                return moves;
            auto target = figure;
            // opponent trigerred
            do {
                figure = (*_myBoard)(_coord.x + option.x, _coord.y + option.y).GetFigure();
                if(figure == nullptr) {
                    moves.emplace_back(Move_t(
                        _coord, sf::Vector2u(_coord.x + option.x, _coord.y + option.y), target));
                    option += backupOption;
                }
            } while(figure == nullptr);
        }
        // If direction is outside the board
        catch(std::out_of_range& e) {
            figure = nullptr;
            continue;
        }
    }
    // Return vector of possible moves
    return moves;
}

} // namespace pamsi
