#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <deque>

#include "Enemy.h"
#include "Level.h"

namespace td {
	class Game
	{
	public:
		Game();
		void Update(const sf::Vector2i& mousePosition);
		void Render(sf::RenderWindow& window) const;

	private:
		Level m_level;
		std::deque<Enemy> m_enemies;

		float m_waveTimer;
		int m_waveEnemyCount;

		void UpdateWaveSpawn();
	};
}
