#include <iostream>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Game.h"
#include "GlobalTime.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(td::constants::k_SCREEN_WIDTH, td::constants::k_SCREEN_HEIGHT), "Tower Defense");

	td::Game game;

	bool windowInFocus = true;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::GainedFocus) windowInFocus = true;
			if (event.type == sf::Event::LostFocus) windowInFocus = false;
		}
		td::GlobalTime::OnFrameBegin();

		if (windowInFocus) {


			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

			game.Update(mousePosition);

			game.Render(window);
		}

		window.display();
	}

	return 0;
}
