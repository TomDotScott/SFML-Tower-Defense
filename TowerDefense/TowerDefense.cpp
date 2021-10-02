#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tower Defense");

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.draw(sf::CircleShape(25));
        window.display();
    }

    return 0;
}