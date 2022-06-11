#ifndef TILE_PAMSI_PROJECT_DEFINE_H
#define TILE_PAMSI_PROJECT_DEFINE_H

#include "figure.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace pamsi {

class Tile_t : public sf::Drawable, public sf::Transformable {
    sf::RectangleShape _shape;
    std::shared_ptr<Figure_t> _figure;

public:
    Tile_t(sf::Vector2f size) : _shape(size), _figure{nullptr} {};

    void SetColor(sf::Color color);
    void SetOutlineColor(sf::Color outlineColor);
    void SetPosition(sf::Vector2f position);
    void SetBorderWidth(float borderWidth);
    std::shared_ptr<Figure_t>& GetFigure() { return _figure; }
    void SetFigure(std::shared_ptr<Figure_t> figure);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // TILE_PAMSI_PROJECT_DEFINE_H