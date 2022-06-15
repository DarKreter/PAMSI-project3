#ifndef BOARD_PAMSI_PROJECT_DEFINE_H
#define BOARD_PAMSI_PROJECT_DEFINE_H

#include <Figure.hpp>
#include <SFML/Graphics.hpp>
#include <Tile.hpp>
#include <memory>
#include <mutex>
#include <vector>

#define fillColor_1 sf::Color::Red
#define fillColor_2 sf::Color::White
#define outlineColor sf::Color::Black

namespace pamsi {
class Board_t : public sf::Drawable {
protected:
    std::vector<std::vector<pamsi::Tile_t>> _tiles;
    std::vector<std::shared_ptr<Figure_t>> _whiteFigures;
    std::vector<std::shared_ptr<Figure_t>> _blackFigures;

    sf::Texture _whitePiece, _blackPiece, _whiteKing, _blackKing;

    float _borderWidth;
    float _tileLength;
    float _figureRadius;

    std::mutex mtx;

    void SetUpTextures();
    void SetUpFiguresGameStart();
    void SetUpFiguresCopy(const Board_t& second);
    void SetUpTiles();

public:
    Board_t(float windowsSize, float borderWidth);
    Board_t(const Board_t& second);
    const Board_t& operator=(const Board_t& second);

    void lock() { mtx.lock(); }
    void unlock() { mtx.unlock(); }

    bool CheckLoseConditions(Team_e player);
    void MoveFigure(pamsi::Move_t move);
    void ChangePieceToKing(std::shared_ptr<Figure_t> figure);

    float GetBorderWidth() const { return _borderWidth; }
    float GetTileLength() const { return _tileLength; }
    float GetFigureRadius() const { return _figureRadius; }
    std::vector<Move_t> GetAllPossibleMoves(Team_e player, bool figureAlreadyTaken) const;
    pamsi::Tile_t& operator()(uint8_t x, uint8_t y);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // BOARD_PAMSI_PROJECT_DEFINE_H