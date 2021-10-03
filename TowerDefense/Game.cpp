#include "Game.h"

#include "GlobalTime.h"
#include "Constants.h"
#include "Helpers.h"


td::Game::Game() :
	m_waveTimer(0.f),
	m_waveEnemyCount(0)
{
	for (int i = 0; i < 10; i++)
	{
		m_enemies.emplace_back(sf::Color::Red);
	}
}

void td::Game::Update(const sf::Vector2i& mousePosition)
{
	UpdateWaveSpawn();

	for (auto& enemy : m_enemies)
	{
		enemy.Update();
	}
}

void td::Game::Render(sf::RenderWindow& window) const
{
	m_level.Render(window);

	for (const auto& enemy : m_enemies)
	{
		enemy.Render(window);
	}
}

void td::Game::UpdateWaveSpawn()
{
	m_waveTimer -= GlobalTime::DeltaTime();

	if (helper_functions::definitely_less_than(m_waveTimer, 0.f))
	{
		if (m_waveEnemyCount < 10) {
			m_enemies[m_waveEnemyCount++].Spawn();

			m_waveTimer = constants::k_timeBetweenSpawn;
		}
	}
}
