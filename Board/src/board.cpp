#include "board.hpp"

namespace pamsi {
void Board_t::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& a : tiles)
        for(auto& tile : a)
            target.draw(tile, states);
}

Board_t::Board_t(float windowsSize, float borderWidth)
{
    float tileLength = (windowsSize / 8.f);

    for(size_t x = 0; x < windowsSize; x += tileLength) {
        std::vector<pamsi::Tile_t> tempVector;
        for(size_t y = 0; y < windowsSize; y += tileLength) {

            pamsi::Tile_t temp(sf::Vector2f(tileLength, tileLength));

            if(!(x % 2) && y % 2)
                temp.SetColor(sf::Color::Red);
            else if(x % 2 && !(y % 2))
                temp.SetColor(sf::Color::Red);
            else
                temp.SetColor(sf::Color::White);

            temp.SetBorderWidth(borderWidth);
            temp.SetOutlineColor(sf::Color::Black);
            temp.SetPosition(sf::Vector2f(x, y));

            tempVector.emplace_back(temp);
        }
        tiles.emplace_back(tempVector);
    }
}
} // namespace pamsi
