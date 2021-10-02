#include <iostream>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(td::constants::k_screenWidth, td::constants::k_screenHeight), "Tower Defense");

    td::Game game;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);


        game.Update(mousePosition);

        game.Render(window);

    	window.display();
    }

    return 0;
}
