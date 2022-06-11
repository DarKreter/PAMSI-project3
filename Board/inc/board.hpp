#ifndef BOARD_PAMSI_PROJECT_DEFINE_H
#define BOARD_PAMSI_PROJECT_DEFINE_H

#include <Figure.hpp>
#include <SFML/Graphics.hpp>
#include <Tile.hpp>
#include <memory>
#include <vector>

#define fillColor_1 sf::Color::Red
#define fillColor_2 sf::Color::White
#define outlineColor sf::Color::Black

namespace pamsi {
class Board_t : public sf::Drawable {
    std::vector<std::vector<pamsi::Tile_t>> _tiles;
    std::vector<std::shared_ptr<Figure_t>> _whiteFigures;
    std::vector<std::shared_ptr<Figure_t>> _blackFigures;

    sf::Texture _whitePawn, _blackPawn;

    void SetUpTextures();
    void SetUpFigures(float windowsSize, float borderWidth);
    void SetUpTiles(float windowsSize, float borderWidth);

    typedef std::vector<std::pair<sf::Vector2i, sf::Vector2i>> movesVector;

public:
    Board_t(float windowsSize, float borderWidth);
    bool CheckLoseConditions(Team_e player);
    movesVector GetAllPossibleMoves(Team_e player);
    pamsi::Tile_t operator()(uint8_t x, uint8_t y);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // BOARD_PAMSI_PROJECT_DEFINE_H