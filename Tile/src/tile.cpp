#include "tile.hpp"

namespace pamsi {

void Tile_t::SetColor(sf::Color color) { _shape.setFillColor(color); }
void Tile_t::SetOutlineColor(sf::Color outlineColor)
{
    _shape.setOutlineColor(outlineColor);
}
void Tile_t::SetPosition(sf::Vector2f position)
{
    _shape.setPosition(position);
}
void Tile_t::SetBorderWidth(float borderWidth)
{
    _shape.setOutlineThickness(-borderWidth / 2.f);
}
void Tile_t::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the entity's transform -- combine it with the one that was
    // passed by the caller
    states.transform *=
        getTransform(); // getTransform() is defined by sf::Transformable

    // apply the texture
    // states.texture = &_texture;

    // draw the vertex array
    target.draw(_shape, states);
}

} // namespace pamsi
