#ifndef MOVE_PAMSI_PROJECT_DEFINE_H
#define MOVE_PAMSI_PROJECT_DEFINE_H

#include <SFML/Graphics.hpp>
#include <memory>

namespace pamsi {

class Figure_t;

class Move_t {
    sf::Vector2u _source;
    sf::Vector2u _destination;
    std::shared_ptr<Figure_t> _attacked;

public:
    Move_t(sf::Vector2u src, sf::Vector2u dest, std::shared_ptr<Figure_t> attck = nullptr)
        : _source{src}, _destination{dest}, _attacked{attck}
    {
    }
    sf::Vector2u GetSource() { return _source; };
    sf::Vector2u GetDestination() { return _destination; };
    std::shared_ptr<Figure_t> GetAttacked() { return _attacked; };

    void SetSource(sf::Vector2u source) { _source = source; }
    void SetDestination(sf::Vector2u dest) { _destination = dest; }
    void SetAttacked(std::shared_ptr<Figure_t> atck) { _attacked = atck; }

    bool operator==(const Move_t& move)
    {
        return _source == move._source && _destination == move._destination;
    }
};

} // namespace pamsi

#endif // MOVE_PAMSI_PROJECT_DEFINE_H