#include "game.hpp"
#include "move.hpp"
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
            std::cout << move.GetSource().x << " " << move.GetSource().y << "\t"
                      << move.GetDestination().x << " " << move.GetDestination().y << "\t"
                      << move.GetAttacked() << std::endl;
        }
        // If there is no moves for player, it's draw
        if(allMoves.empty()) {
            std::cout << "DRAW!" << std::endl;
            std::cout << "GAME OVER!" << std::endl;
            exit(0);
        }

        // Get valid move from player
        Move_t playerMove = GetValidMoveFromPlayer(allMoves);

        // Move
        board.MoveFigure(playerMove);

        // Change player
        if(whoseTurn == pamsi::Team_e::white)
            whoseTurn = pamsi::Team_e::black;
        else if(whoseTurn == pamsi::Team_e::black)
            whoseTurn = pamsi::Team_e::white;
    }
}

Move_t GetValidMoveFromPlayer(std::vector<Move_t>& allMoves)
{
    sf::Vector2u source, dest;
    std::vector<Move_t>::iterator result;
    Move_t myMove(source, dest);
    do {

        // Get move from player
        std::cin >> source.x >> source.y;
        std::cin >> dest.x >> dest.y;

        myMove.SetSource(source);
        myMove.SetDestination(dest);
        // Check if it's valid
        result =
            std::find_if(std::begin(allMoves), std::end(allMoves), [&myMove](auto& currentMove) {
                if(myMove == currentMove)
                    return true;
                return false;
            });

        if(result == std::end(allMoves))
            std::cout << "Invalid move!" << std::endl;

    } while(result == std::end(allMoves));

    std::cout << "Valid move!" << std::endl;

    return myMove;
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
