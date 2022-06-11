#include "figure.hpp"

namespace pamsi {

void Figure_t::SetPosition(sf::Vector2f position) { _shape.setPosition(position); }

void Figure_t::SetCoordinates(sf::Vector2u coord)
{
    _coord.x = coord.x;
    _coord.y = coord.y;
}

void Figure_t::SetTexture(sf::Texture& texture)
{
    _shape.setTexture(&texture); // texture is a sf::Texture
    _shape.setTextureRect(sf::IntRect(0, 0, 296, 275));
}
void Figure_t::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the entity's transform -- combine it with the one that was
    // passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // apply the texture
    // states.texture = &_texture;

    // draw the vertex array
    target.draw(_shape, states);
}

std::vector<sf::Vector2i> Figure_t::GetPossibleMoves()
{
    auto normalMoves = GetNormalMoves();
    auto attackMoves = GetAttackMoves();
    decltype(normalMoves) allMoves;
    allMoves.reserve(normalMoves.size() + attackMoves.size()); // preallocate memory
    allMoves.insert(allMoves.end(), normalMoves.begin(), normalMoves.end());
    allMoves.insert(allMoves.end(), attackMoves.begin(), attackMoves.end());

    return allMoves;
}

} // namespace pamsi
