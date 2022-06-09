#ifndef BOARD_PAMSI_PROJECT_DEFINE_H
#define BOARD_PAMSI_PROJECT_DEFINE_H

#include <SFML/Graphics.hpp>
#include <Tile.hpp>
#include <array>

namespace pamsi {

class Board_t : public sf::Drawable {
#define fillColor_1 sf::Color::Red
#define fillColor_2 sf::Color::White
#define outlineColor sf::Color::Black
    std::vector<std::vector<pamsi::Tile_t>> tiles;

public:
    Board_t(float windowsSize, float borderWidth);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // BOARD_PAMSI_PROJECT_DEFINE_H