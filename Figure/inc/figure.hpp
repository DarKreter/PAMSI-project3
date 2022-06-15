#ifndef FIGURE_PAMSI_PROJECT_DEFINE_H
#define FIGURE_PAMSI_PROJECT_DEFINE_H

#include "move.hpp"
#include <SFML/Graphics.hpp>

namespace pamsi {

class Board_t;

/**
 * @brief enumeration type for distinguish white and black team
 *
 */
enum class Team_e
{
    white,
    black
};

/**
 * @brief virtual class figure that represents any figure on the board
 *
 */
class Figure_t : public sf::Drawable, public sf::Transformable {
protected:
    sf::CircleShape _shape;   // SFML shape
    sf::Vector2u _coord;      // Coordinates of figure
    Team_e _team;             // figures team
    pamsi::Board_t* _myBoard; // board that figure is on

    /**
     * @brief Set the Position object
     *
     * @param position setting position in gui
     */
    void SetPosition(sf::Vector2f position);

public:
    /**
     * @brief type identifying what the figure is
     */
    enum class WhoAmI
    {
        Piece,
        King
    };

    /**
     * @brief Construct a new Figure_t object
     *
     * @param radius setting figure radius (for gui purposes)
     * @param whoAmI setting who the figure is
     */
    Figure_t(float radius, WhoAmI whoAmI) : _shape(radius), _myBoard{NULL}, _whoAmI{whoAmI} {};

    /**
     * @brief Setter for _texture
     */
    void SetTexture(sf::Texture& texture);
    /**
     * @brief Setter for the Coordinates of figure
     */
    void SetCoordinates(sf::Vector2u coord);
    /**
     * @brief Setter for the Team
     */
    void SetTeam(Team_e team) { _team = team; }
    /**
     * @brief Setter for the Board
     */
    void SetBoard(pamsi::Board_t* board) { _myBoard = board; }

    /**
     * @brief Getter for the Coordinates
     */
    sf::Vector2u& GetCoordinates() { return _coord; }
    /**
     * @brief Getter for team
     */
    Team_e& GetTeam() { return _team; }
    /**
     * @brief Getter for the WhoAmI
     */
    WhoAmI GetWhoAmI() { return _whoAmI; }

    /**
     * @brief Returns vector of all possible moves that figure can do from its current position
     */
    std::vector<pamsi::Move_t> GetPossibleMoves();
    /**
     * @brief Returns vector of all possible normal moves that figure can do from its current
     * position
     */
    virtual std::vector<pamsi::Move_t> GetNormalMoves() = 0;
    /**
     * @brief Returns vector of all possible attack moves that figure can do from its current
     * position
     */
    virtual std::vector<pamsi::Move_t> GetAttackMoves() = 0;

protected:
    WhoAmI _whoAmI;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace pamsi

#endif // FIGURE_PAMSI_PROJECT_DEFINE_H