#include "Level.h"

td::Level::Level()
{
	m_backgroundTexture.loadFromFile("Assets/Track1.png");
	m_backgroundSprite.setTexture(m_backgroundTexture);
}

void td::Level::Render(sf::RenderWindow& window) const
{
	window.draw(m_backgroundSprite);
}
