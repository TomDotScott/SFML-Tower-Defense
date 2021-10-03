#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "Level.h"

namespace td {
	class Game
	{
	public:
		void Update(const sf::Vector2i& mousePosition);
		void Render(sf::RenderWindow& window) const;

	private:
		Level m_level;
		Enemy m_enemy;
	};
}
