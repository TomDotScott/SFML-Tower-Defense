#include "Game.h"

#include "GlobalTime.h"

void td::Game::Update(const sf::Vector2i& mousePosition)
{
	m_enemy.Update();
}

void td::Game::Render(sf::RenderWindow& window) const
{
	m_level.Render(window);

	m_enemy.Render(window);
}
