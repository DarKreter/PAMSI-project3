#ifndef TILE_PAMSI_PROJECT_DEFINE_H
#define TILE_PAMSI_PROJECT_DEFINE_H

#include <SFML/Graphics.hpp>

namespace pamsi {

class Tile_t : public sf::Drawable, public sf::Transformable {
    sf::RectangleShape _shape;
    // sf::Texture _texture;

public:
    Tile_t(sf::Vector2f size) : _shape(size){};

    void SetColor(sf::Color color);
    void SetOutlineColor(sf::Color outlineColor);
    void SetPosition(sf::Vector2f position);
    void SetBorderWidth(float borderWidth);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // TILE_PAMSI_PROJECT_DEFINE_H