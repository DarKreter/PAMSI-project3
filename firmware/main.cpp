#include "board.hpp"
#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

constexpr size_t windowsSize = 1000;
constexpr size_t borderWidth = 5.f;

int main()
{
    cout << "Hello World!" << endl;

    sf::VideoMode();

    sf::RenderWindow window(sf::VideoMode(windowsSize, windowsSize),
                            "Checkers!", sf::Style::Default);

    // sf::Font font;
    // if(!font.loadFromFile("FontAlexa3.ttf")) {
    //     return 0;
    //     // error...
    // }
    // sf::Text text;

    // text.setFont(font); // font is a sf::Font
    // text.setString("Hello world!");
    // text.setCharacterSize(100); // in pixels, not points!
    // text.setFillColor(sf::Color(0xff5f51ff));
    // text.setStyle(sf::Text::Bold);

    pamsi::Board_t plansza(windowsSize, borderWidth);

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

        // draw everything here...
        sf::Texture whitePawn, blackPawn;

        if(!whitePawn.loadFromFile("whitePawn.jpg"))
            break;

        if(!blackPawn.loadFromFile("blackPawn.jpg"))
            break;

        whitePawn.setSmooth(true);
        blackPawn.setSmooth(true);

        // for(size_t x = 0; x < windowsSize; x += tileLength) {
        //     for(size_t y = 0; y < windowsSize; y += tileLength) {
        //         sf::CircleShape shape((tileLength - borderWidth) / 2.f);

        //         if(((y == 0 || y == 2 * tileLength) && x % 2) ||
        //            (y == tileLength && !(x % 2))) {
        //             shape.setTexture(&blackPawn); // texture is a sf::Texture
        //             shape.setTextureRect(sf::IntRect(0, 0, 296, 275));
        //             shape.setPosition(x + borderWidth / 2.f,
        //                               y + borderWidth / 2.f);
        //             window.draw(shape);
        //         }
        //         if(((y == 5 * tileLength || y == 7 * tileLength) && !(x % 2))
        //         ||
        //            (y == 6 * tileLength && x % 2)) {
        //             shape.setTexture(&whitePawn); // texture is a sf::Texture
        //             shape.setTextureRect(sf::IntRect(0, 0, 286, 297));
        //             shape.setPosition(x + borderWidth / 2.f,
        //                               y + borderWidth / 2.f);
        //             window.draw(shape);
        //         }
        //     }
        // }

        window.draw(plansza);
        // end the current frame
        window.display();
    }

    return 0;
}
