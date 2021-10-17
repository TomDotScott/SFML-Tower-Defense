#include "Game.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "GlobalTime.h"
#include "Constants.h"
#include "Helpers.h"


td::Game::Game() :
	m_waveTimer(0.f),
	m_waveEnemyCount(0)
{
	ReadLevelData("Assets/waves.csv");

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

			m_waveTimer = constants::k_TIME_BETWEEN_SPAWN;
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
		if(waveNum > constants::k_MAX_WAVES){ break; }

		std::stringstream sep(line);
		std::string field;

		std::vector<EnemyData> waveEnemyData;

		int charNum = 0;
		// per column
		while (std::getline(sep, field, ','))
		{

			if(field.size() != 1)
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
