#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <deque>

#include "Constants.h"
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

		float m_timeBetweenSpawns;

		int m_enemiesSpawnedSoFar;
		int m_enemyCountThisWave;

		int m_currentWave;
		bool m_shouldStartNextWave;

		struct EnemyData
		{
			explicit EnemyData(const eEnemyType t) : m_Type(t) { }

			eEnemyType m_Type;
		};

		// Each index of the array corresponds to a specific wave
		std::array<std::vector<EnemyData>, constants::k_MAX_WAVES> m_gameEnemyData;

		void StartSpawnNextWave();
		void UpdateWaveSpawn();
		bool ReadLevelData(const std::string& fileName);
	};
}
