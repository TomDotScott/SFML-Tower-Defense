#include "Game.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "GlobalTime.h"
#include "Constants.h"
#include "Helpers.h"


td::Game::Game() :
	m_timeBetweenSpawns(0.f),
	m_enemiesSpawnedSoFar(0),
	m_enemyCountThisWave(0),
	m_currentWave(0),
	m_shouldStartNextWave(true)
{
	ReadLevelData("Assets/waves.csv");

	m_towers.emplace_back(TowerBase({ 200, 270 }));
}

void td::Game::Update(const sf::Vector2i& mousePosition)
{
	// printf("Mouse Position: %i, %i\n", mousePosition.x, mousePosition.y);
	if (m_shouldStartNextWave) {
		StartSpawnNextWave();
		m_shouldStartNextWave = false;
	}
	else
	{
		UpdateWaveSpawn();
	}

	if (!m_enemies.empty()) {
		// Update the enemies
		for (auto& enemy : m_enemies)
		{
			enemy.Update();
		}

		// Update the towers
		for(auto& tower : m_towers)
		{
			tower.Update();
		}

		// If the enemies are dead, or they have completed the track, remove them
		std::erase_if(m_enemies, 
			[](const Enemy& e)
			{
				return e.GetState() != Enemy::eState::e_alive;
			}
		);
	}
	else
	{
		m_currentWave++;
		m_enemiesSpawnedSoFar = 0;
		m_shouldStartNextWave = true;
	}
}

void td::Game::Render(sf::RenderWindow& window) const
{
	m_level.Render(window);

	for (const auto& tower : m_towers)
	{
		tower.Render(window);
	}

	for (const auto& enemy : m_enemies)
	{
		enemy.Render(window);
	}
}

void td::Game::StartSpawnNextWave()
{
	// Get the data loaded from the csv
	const std::vector<EnemyData>& enemyData = m_gameEnemyData[m_currentWave];

	// Clear the enemies deque
	m_enemies.clear();

	m_enemyCountThisWave = static_cast<int>(enemyData.size());

	// Loop through and load the m_enemies deque
	for (const auto& enemy : enemyData)
	{
		m_enemies.emplace_back(enemy.m_Type);
	}
}

void td::Game::UpdateWaveSpawn()
{
	m_timeBetweenSpawns -= GlobalTime::DeltaTime();

	if (helper_functions::definitely_less_than(m_timeBetweenSpawns, 0.f))
	{
		if (m_enemiesSpawnedSoFar < m_enemyCountThisWave) {
			m_enemies[m_enemiesSpawnedSoFar++].Spawn();

			m_timeBetweenSpawns = constants::k_TIME_BETWEEN_SPAWN;
		}
	}
}

bool td::Game::ReadLevelData(const std::string& fileName)
{
	// Open the csv file to read
	std::ifstream waveFile(fileName);

	// Ensure the file has been opened
	if (!waveFile.is_open()) { return false; }

	std::string line;

	int waveNum = 0;
	// per row
	while (std::getline(waveFile, line))
	{
		if (waveNum > constants::k_MAX_WAVES) { break; }

		std::stringstream sep(line);
		std::string field;

		std::vector<EnemyData> waveEnemyData;

		int charNum = 0;
		// per column
		while (std::getline(sep, field, ','))
		{

			if (field.size() != 1)
			{
				printf("\nUnknown value %s at Line %i, char %i in %s\n", field.c_str(), waveNum + 1, (charNum + 1) * 2, fileName.c_str());
				return false;
			}

			std::cout << field << ", ";

			// The values being read are characters, treat them as such
			switch (field.c_str()[0])
			{
			case 'R':
				waveEnemyData.emplace_back(eEnemyType::e_red);
				break;
			case 'G':
				waveEnemyData.emplace_back(eEnemyType::e_green);
				break;
			case 'B':
				waveEnemyData.emplace_back(eEnemyType::e_blue);
				break;
			default:
				printf("Unknown enemy type read from %s", fileName.c_str());
				break;
			}

			charNum++;
		}

		std::cout << "\n" << std::endl;


		m_gameEnemyData[waveNum] = waveEnemyData;
		waveNum++;
	}

	printf("Successfully loaded %i waves\n", waveNum);
	return true;
}
