#include <SFML/Window.hpp>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    sf::VideoMode();

    sf::Window window(sf::VideoMode(sf::Vector2u(800, 600)), "My window");

    this_thread::sleep_for(chrono::seconds(5));

    return 0;
}
