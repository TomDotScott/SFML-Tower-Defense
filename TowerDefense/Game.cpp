#include "Game.h"

void td::Game::Update(const sf::Vector2i& mousePosition)
{

}

void td::Game::Render(sf::RenderWindow& window) const
{
	m_level.Render(window);
}
