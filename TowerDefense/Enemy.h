#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

namespace td {
	class Enemy
	{
	public:
		Enemy();

		void Update();

		void Render(sf::RenderWindow& window) const;


	private:
		int m_currentWaypointIndex;
		sf::Vector2f m_currentGoalPosition;
		sf::Vector2f m_currentMovementVector;

		float m_speed;
		sf::Vector2f m_position;

		bool m_visible;

		void Move();
		void CheckWaypoints();
	};
}
