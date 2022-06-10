#ifndef FIGURE_PAMSI_PROJECT_DEFINE_H
#define FIGURE_PAMSI_PROJECT_DEFINE_H

#include <SFML/Graphics.hpp>

namespace pamsi {

class Figure_t : public sf::Drawable, public sf::Transformable {
protected:
    sf::CircleShape _shape;

public:
    Figure_t(float radius) : _shape(radius){};

    void SetTexture(sf::Texture& texture);
    void SetPosition(sf::Vector2f position);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // FIGURE_PAMSI_PROJECT_DEFINE_H