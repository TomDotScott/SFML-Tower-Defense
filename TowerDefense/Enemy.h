#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

namespace td {
	class Enemy
	{
	public:
		Enemy();
		Enemy(sf::Color colour);

		void Update();

		void Render(sf::RenderWindow& window) const;

		enum class eState
		{
			e_alive,
			e_dead,
			e_complete
		};

		eState GetState() const { return m_state; }

		void Spawn();

	private:
		int m_currentWaypointIndex;
		sf::Vector2f m_currentGoalPosition;
		sf::Vector2f m_currentMovementVector;

		float m_speed;
		sf::Vector2f m_position;

		sf::Color m_colour;

		bool m_visible;
		eState m_state;

		void Move();
		void CheckWaypoints();
		void CalculateMovementVector();
	};
}
