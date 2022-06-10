#include "game.hpp"

namespace pamsi {
void Game([[maybe_unused]] pamsi::Board_t& board)
{
    while(1)
        ;
}

constexpr size_t windowsSize = 1000;
constexpr size_t borderWidth = 5.f;

void sfmlLoop(pamsi::Board_t& board)
{
    sf::RenderWindow window(sf::VideoMode(windowsSize, windowsSize),
                            "Checkers!", sf::Style::Default);

    window.setFramerateLimit(60);

    // run the program as long as the window is open
    while(window.isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        sf::Event event;
        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        window.draw(board);
        // end the current frame
        window.display();
    }
}

} // namespace pamsi
