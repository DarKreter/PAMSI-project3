#include "game.hpp"
#include <iostream>

namespace pamsi {
void Game(pamsi::Board_t& board)
{
    // white always starts
    pamsi::Team_e whoseTurn = pamsi::Team_e::white;
    while(true) {
        // Check lose conditions
        if(board.CheckLoseConditions(whoseTurn)) {
            std::cout << "GAME OVER!" << std::endl;
            if(whoseTurn == pamsi::Team_e::white)
                std::cout << "BLACK WON!" << std::endl;
            else if(whoseTurn == pamsi::Team_e::black)
                std::cout << "WHITE WON!" << std::endl;
            exit(0);
        }

        // Get all possible moves for current player
        auto allMoves = board.GetAllPossibleMoves(whoseTurn);

        for(auto& move : allMoves) {
            std::cout << move.first.x << " " << move.first.y << "\t" << move.second.x << " "
                      << move.second.y << std::endl;
        }
        // If there is no moves for him, it's draw
        if(allMoves.empty()) {
            std::cout << "DRAW!" << std::endl;
            std::cout << "GAME OVER!" << std::endl;
            exit(0);
        }

        while(true)
            ;

        // Get move from player

        // Check if it's valid

        // Move

        // Change player
        if(whoseTurn == pamsi::Team_e::white)
            whoseTurn = pamsi::Team_e::black;
        else if(whoseTurn == pamsi::Team_e::black)
            whoseTurn = pamsi::Team_e::white;
    }
}

constexpr size_t windowsSize = 1000;
constexpr size_t borderWidth = 5.f;

void sfmlLoop(pamsi::Board_t& board)
{
    sf::RenderWindow window(sf::VideoMode(windowsSize, windowsSize), "Checkers!",
                            sf::Style::Default);

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

    exit(0);
}

} // namespace pamsi
