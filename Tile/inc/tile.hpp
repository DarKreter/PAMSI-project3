#ifndef TILE_PAMSI_PROJECT_DEFINE_H
#define TILE_PAMSI_PROJECT_DEFINE_H

#include <SFML/Graphics.hpp>
#include <memory>

namespace pamsi {

class Figure_t;

/**
 * @brief Class that represents single tile on the board
 * It has information about figure on it
 */
class Tile_t : public sf::Drawable, public sf::Transformable {
    sf::RectangleShape _shape;
    // Figure standing on this tile
    std::shared_ptr<Figure_t> _figure;

public:
    /**
     * @brief Construct a new Tile_t object
     *
     * @param size defines a size of tile in gui
     */
    Tile_t(sf::Vector2f size) : _shape(size), _figure{nullptr} {};

    /**
     * @brief Set the Color object
     *
     * @param color color to set
     */
    void SetColor(sf::Color color);
    /**
     * @brief Set the Outline Color object
     *
     * @param outlineColor color of the outline
     */
    void SetOutlineColor(sf::Color outlineColor);
    /**
     * @brief Set the Position object
     *
     * @param position position of tile in gui
     */
    void SetPosition(sf::Vector2f position);
    /**
     * @brief Set the Border Width object
     *
     * @param borderWidth width of the outline
     */
    void SetBorderWidth(float borderWidth);
    /**
     * @brief Getter for the _figure variable
     *
     * @return std::shared_ptr<Figure_t>
     */
    std::shared_ptr<Figure_t> GetFigure() { return _figure; }
    /**
     * @brief Setter for the _figure variable
     *
     * @param figure
     */
    void SetFigure(std::shared_ptr<Figure_t> figure);

private:
    /**
     * @brief function that allows Tile to be drawed by SFML
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // TILE_PAMSI_PROJECT_DEFINE_H