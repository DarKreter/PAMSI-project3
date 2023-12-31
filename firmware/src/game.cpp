#include "game.hpp"
#include "Algorithms.hpp"
#include "move.hpp"
#include <iostream>
#include <queue>
#include <thread>

constexpr size_t windowsSize = 1000;
constexpr size_t borderWidth = 5.f;

namespace pamsi {
void Game(pamsi::Board_t& board, function whiteMove, function blackMove)
{
    // white always starts
    pamsi::Team_e whoseTurn = pamsi::Team_e::white;
    std::shared_ptr<Figure_t> lastMovedFigure = nullptr;
    bool figureTaken = false;

    while(true) {

        // Check lose conditions
        if(!figureTaken && board.CheckLoseConditions(whoseTurn)) {
            std::cout << "GAME OVER!" << std::endl;
            if(whoseTurn == pamsi::Team_e::white)
                std::cout << "BLACK WON!" << std::endl;
            else if(whoseTurn == pamsi::Team_e::black)
                std::cout << "WHITE WON!" << std::endl;
            getchar();
            exit(0);
        }

        // Get all possible moves for current player (if last move was strike, we check only strikes
        // for lastMovedFigure)
        std::vector<Move_t> allMoves;
        if(!figureTaken)
            allMoves = std::move(board.GetAllPossibleMoves(whoseTurn, figureTaken));
        else
            allMoves = std::move(lastMovedFigure->GetAttackMoves());

        // DEBUG
        // for(auto& move : allMoves) {
        //     std::cout << move.GetSource().x << " " << move.GetSource().y << "\t"
        //               << move.GetDestination().x << " " << move.GetDestination().y << "\t"
        //               << move.GetTaken() << std::endl;
        // }
        // std::cout << std::endl;

        Move_t playerMove;
        // If there is no moves for player and he didn't do any move already
        if(!figureTaken && allMoves.empty()) {
            std::cout << "DRAW!" << std::endl;
            std::cout << "GAME OVER!" << std::endl;
            // getchar();
            exit(0);
        }
        // He don't have moves but already make some
        else if(figureTaken && allMoves.empty()) {
            figureTaken = false;
        }
        // He has move
        else {
            // Get valid move from proper function
            if(whoseTurn == pamsi::Team_e::white)
                playerMove = whiteMove(allMoves, whoseTurn, board);
            else if(whoseTurn == pamsi::Team_e::black)
                playerMove = blackMove(allMoves, whoseTurn, board);

            // Move
            board.lock();
            board.MoveFigure(playerMove);
            board.unlock();
            // log last moved figure
            lastMovedFigure =
                board(playerMove.GetDestination().x, playerMove.GetDestination().y).GetFigure();

            if(playerMove.GetTaken()) {
                figureTaken = true;
                continue;
            }
            else
                figureTaken = false;
        }

        // Check if piece reach last row and then change it to king
        // also hange player
        if(whoseTurn == pamsi::Team_e::white) {
            whoseTurn = pamsi::Team_e::black;
            if(lastMovedFigure->GetCoordinates().y == 0) {
                board.ChangePieceToKing(lastMovedFigure);
            }
        }
        else if(whoseTurn == pamsi::Team_e::black) {
            whoseTurn = pamsi::Team_e::white;

            if(lastMovedFigure->GetCoordinates().y == 7) {
                board.ChangePieceToKing(lastMovedFigure);
            }
        }
    }
}

sf::Vector2u GetPressedTileCoord(sf::Vector2u mouse, sf::Vector2u size)
{
    size_t x = (float(mouse.x) / float(size.x)) * 8.f;
    size_t y = (float(mouse.y) / float(size.y)) * 8.f;

    // std::cout << x << "," << y << std::endl;
    return sf::Vector2u(x, y);
}

void sfmlLoop(pamsi::Board_t& board, std::queue<sf::Vector2u>& mouseQueue, bool& reading,
              std::mutex& queueMutex)
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
            // if mouse was pressed
            else if(event.type == sf::Event::MouseButtonPressed) {
                // and we have enabled reading flag
                if(event.mouseButton.button == sf::Mouse::Left && reading) {
                    // get pressed tile
                    auto tile = GetPressedTileCoord(
                        sf::Vector2u(event.mouseButton.x, event.mouseButton.y), window.getSize());

                    queueMutex.lock();
                    // if queue is full, remove last element
                    if(mouseQueue.size() == 10)
                        mouseQueue.pop();
                    // Add pressed tile to queue
                    mouseQueue.push(tile);
                    queueMutex.unlock();
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        // draw board
        board.lock();
        window.draw(board);
        board.unlock();
        // end the current frame
        window.display();
    }

    exit(0);
}

} // namespace pamsi
