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

/**
 * @brief class that represents board
 *
 */
class Board_t : public sf::Drawable {
protected:
    // two dimensional array of tiles (8x8)
    std::vector<std::vector<pamsi::Tile_t>> _tiles;
    // vector of figures from white team
    std::vector<std::shared_ptr<Figure_t>> _whiteFigures;
    // vector of figures from black team
    std::vector<std::shared_ptr<Figure_t>> _blackFigures;

    // textures for all types of figures
    sf::Texture _whitePiece, _blackPiece, _whiteKing, _blackKing;

    float _borderWidth;
    float _tileLength;
    float _figureRadius;

    std::mutex mtx;

    /**
     * @brief Setting up textures
     *
     */
    void SetUpTextures();
    /**
     * @brief Adding figures in start positions
     */
    void SetUpFiguresGameStart();
    /**
     * @brief copying figures from the second board
     *
     * @param second board
     */
    void SetUpFiguresCopy(const Board_t& second);
    /**
     * @brief Setting tiles in starting position for main board
     */
    void SetUpTiles();
    /**
     * @brief Setting tiles copied board
     */
    void SetUpTilesCopy();

public:
    Board_t(float windowsSize, float borderWidth);
    Board_t(const Board_t& second);
    const Board_t& operator=(const Board_t& second);

    /**
     * @brief locking board mutex
     */
    void lock() { mtx.lock(); }
    /**
     * @brief unlocking board mutex
     *
     */
    void unlock() { mtx.unlock(); }

    /**
     * @brief Checking if current position is lost
     *
     * @param player for this player it will be checked
     */
    bool CheckLoseConditions(Team_e player);
    /**
     * @brief Moving figure on board
     *
     * @param move move to do
     */
    void MoveFigure(pamsi::Move_t move);
    /**
     * @brief Changing piece into king
     *
     * @param figure piece to tranform
     */
    void ChangePieceToKing(std::shared_ptr<Figure_t> figure);

    /**
     * @brief Getter for border width
     */
    float GetBorderWidth() const { return _borderWidth; }
    /**
     * @brief Getter for tile length
     */
    float GetTileLength() const { return _tileLength; }
    /**
     * @brief Getter for figure radius
     */
    float GetFigureRadius() const { return _figureRadius; }
    /**
     * @brief returns all possible moves for chosen player for current configuration of board.
     *
     * @param player chosen player
     * @param figureAlreadyTaken if set to true, only attack moves will be checked
     */
    std::vector<Move_t> GetAllPossibleMoves(Team_e player, bool figureAlreadyTaken) const;

    /**
     * @brief Getter for tile based on coordinates

     * @return pamsi::Tile_t& tile returned by reference
     */
    pamsi::Tile_t& operator()(uint8_t x, uint8_t y);
    const std::vector<std::shared_ptr<pamsi::Figure_t>>& GetWhiteFigures() const
    {
        return _whiteFigures;
    }
    const std::vector<std::shared_ptr<pamsi::Figure_t>>& GetBlackFigures() const
    {
        return _blackFigures;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // BOARD_PAMSI_PROJECT_DEFINE_H