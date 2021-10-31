#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "EnemyStats.h"

namespace td {
	class Enemy
	{
	public:
		Enemy();
		Enemy(eEnemyType type);

		void Update();

		void Render(sf::RenderWindow& window) const;

		void TakeDamage(int dmgAmount);

		enum class eState
		{
			e_alive,
			e_dead,
			e_complete
		};

		eState GetState() const { return m_state; }
		sf::Vector2f GetPosition() const { return m_position; }
		sf::Vector2f GetMovementVector() const { return m_currentMovementVector; }

		bool IsActive() const { return m_visible; }

		void Spawn();

	private:
		int m_currentWaypointIndex;
		sf::Vector2f m_currentGoalPosition;
		sf::Vector2f m_currentMovementVector;

		EnemyStats m_stats;

		sf::Vector2f m_position;

		bool m_visible;
		eState m_state;

		void Move();
		void CheckWaypoints();
		void CalculateMovementVector();
	};
}
