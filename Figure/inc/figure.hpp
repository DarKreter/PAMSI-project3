#ifndef FIGURE_PAMSI_PROJECT_DEFINE_H
#define FIGURE_PAMSI_PROJECT_DEFINE_H

#include "move.hpp"
#include <SFML/Graphics.hpp>

namespace pamsi {

class Board_t;

enum class Team_e
{
    white,
    black
};

class Figure_t : public sf::Drawable, public sf::Transformable {
public:
    sf::CircleShape _shape;
    sf::Vector2u _coord;
    Team_e _team;
    pamsi::Board_t* _myBoard;

    void SetPosition(sf::Vector2f position);

    enum class WhoAmI
    {
        Piece,
        King
    } _whoAmI;

public:
    Figure_t(float radius, WhoAmI whoAmI) : _shape(radius), _myBoard{NULL}, _whoAmI{whoAmI} {};

    void SetTexture(sf::Texture& texture);
    void SetCoordinates(sf::Vector2u coord);
    void SetTeam(Team_e team) { _team = team; }
    void SetBoard(pamsi::Board_t* board) { _myBoard = board; }

    sf::Vector2u& GetCoordinates() { return _coord; }
    Team_e& GetTeam() { return _team; }

    std::vector<pamsi::Move_t> GetPossibleMoves();
    virtual std::vector<pamsi::Move_t> GetNormalMoves() = 0;
    virtual std::vector<pamsi::Move_t> GetAttackMoves() = 0;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // FIGURE_PAMSI_PROJECT_DEFINE_H