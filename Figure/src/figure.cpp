#include "figure.hpp"
#include "board.hpp"
#include <iostream>

namespace pamsi {

void Figure_t::SetPosition(sf::Vector2f position) { _shape.setPosition(position); }

// Calculate gui position from its position on board
static inline sf::Vector2f CalcPos(float x, float y, float tileLength, float borderWidth)
{
    return sf::Vector2f(x * tileLength + borderWidth / 2.f + (tileLength - borderWidth) * 0.05f,
                        y * tileLength + borderWidth / 2.f + (tileLength - borderWidth) * 0.05f);
}

void Figure_t::SetCoordinates(sf::Vector2u coord)
{
    // Set position on window
    this->SetPosition(
        CalcPos(coord.x, coord.y, _myBoard->GetTileLength(), _myBoard->GetBorderWidth()));
    // Set coordinates
    _coord = coord;
}

void Figure_t::SetTexture(sf::Texture& texture)
{
    _shape.setTexture(&texture); // texture is a sf::Texture
    _shape.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
}
void Figure_t::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the entity's transform -- combine it with the one that was
    // passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // draw shape
    target.draw(_shape, states);
}

std::vector<pamsi::Move_t> Figure_t::GetPossibleMoves()
{
    // Get normal and attack moves
    auto normalMoves = GetNormalMoves();
    auto attackMoves = GetAttackMoves();
    decltype(normalMoves) allMoves;
    // combine them together
    allMoves.reserve(normalMoves.size() + attackMoves.size()); // preallocate memory
    allMoves.insert(allMoves.end(), normalMoves.begin(), normalMoves.end());
    allMoves.insert(allMoves.end(), attackMoves.begin(), attackMoves.end());

    return allMoves;
}

} // namespace pamsi
