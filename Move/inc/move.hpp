#ifndef MOVE_PAMSI_PROJECT_DEFINE_H
#define MOVE_PAMSI_PROJECT_DEFINE_H

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <memory>

namespace pamsi {

class Figure_t;

/**
 * @brief class that represents move.
 *
 */
class Move_t {
    // source of move
    sf::Vector2u _source;
    // destination of move
    sf::Vector2u _destination;
    // taken opponent with move (if nothing is taken _target is equal nullptr)
    std::shared_ptr<Figure_t> _target;

public:
    Move_t(sf::Vector2u src, sf::Vector2u dest, std::shared_ptr<Figure_t> trgt = nullptr)
        : _source{src}, _destination{dest}, _target{trgt}
    {
    }
    Move_t() : Move_t(sf::Vector2u(INT_MAX, INT_MAX), sf::Vector2u(INT_MAX, INT_MAX)){};
    /**
     * @brief Getter for the source
     */
    sf::Vector2u GetSource() { return _source; };
    /**
     * @brief Getter for the destinantion
     */
    sf::Vector2u GetDestination() { return _destination; };
    /**
     * @brief Getter for the target
     */
    std::shared_ptr<Figure_t> GetTaken() { return _target; };

    /**
     * @brief Setter for the source
     */
    void SetSource(sf::Vector2u source) { _source = source; }
    /**
     * @brief Setter for the destinantion
     */
    void SetDestination(sf::Vector2u dest) { _destination = dest; }
    /**
     * @brief Setter for the target
     */
    void SetTarget(std::shared_ptr<Figure_t> atck) { _target = atck; }

    /**
     * @brief compare operator
     */
    bool operator==(const Move_t& move)
    {
        return _source == move._source && _destination == move._destination;
    }
};

} // namespace pamsi

#endif // MOVE_PAMSI_PROJECT_DEFINE_H