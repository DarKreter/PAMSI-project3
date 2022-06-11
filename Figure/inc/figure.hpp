#ifndef FIGURE_PAMSI_PROJECT_DEFINE_H
#define FIGURE_PAMSI_PROJECT_DEFINE_H

#include <SFML/Graphics.hpp>
#include <list>

namespace pamsi {

enum class Team_e
{
    white,
    black
};

class Figure_t : public sf::Drawable, public sf::Transformable {
protected:
    sf::CircleShape _shape;
    sf::Vector2u _coord;
    Team_e _team;

public:
    Figure_t(float radius) : _shape(radius){};

    void SetTexture(sf::Texture& texture);
    void SetPosition(sf::Vector2f position);
    void SetCoordinates(sf::Vector2u coord);
    void SetTeam(Team_e team) { _team = team; }
    virtual std::list<sf::Vector2u> GetPossibleMoves() = 0;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // FIGURE_PAMSI_PROJECT_DEFINE_H