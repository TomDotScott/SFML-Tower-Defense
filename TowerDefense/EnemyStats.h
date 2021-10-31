#pragma once

namespace td
{
	enum class eEnemyType {
		e_red, e_green, e_blue
	};

	struct EnemyStats
	{
		EnemyStats(const int health, const float speed, const eEnemyType type) :
			m_Health(health),
			m_Speed(speed),
			m_Type(type)
		{

		}

		int m_Health;
		float m_Speed;
		eEnemyType m_Type;
	};

	inline const extern EnemyStats k_RED_STATS{
		100, 100.f, eEnemyType::e_red
	};

	inline const extern EnemyStats k_BLUE_STATS{
		150, 150.f, eEnemyType::e_blue
	};

	inline const extern EnemyStats k_GREEN_STATS{
		300, 250.f, eEnemyType::e_green
	};
}
