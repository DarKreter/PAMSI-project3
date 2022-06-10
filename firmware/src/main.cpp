#include "board.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

using namespace std;

constexpr size_t windowsSize = 1000;
constexpr size_t borderWidth = 5.f;

int main()
{
    // sf::VideoMode();
    // sf::RenderWindow window(sf::VideoMode(windowsSize, windowsSize),
    //                         "Checkers!", sf::Style::Default);

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

    // pamsi::Board_t board(windowsSize, borderWidth);

    std::thread sfmlLoop(pamsi::sfmlLoop);
    // std::thread realGame(pamsi::Game, &board);

    sfmlLoop.join();
    // realGame.join();

    return 0;
}
