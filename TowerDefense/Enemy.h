#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

namespace td {
	enum class eEnemyType {
		e_red, e_green, e_blue
	};

	class Enemy
	{
	public:
		Enemy();
		Enemy(eEnemyType type);

		void Update();

		void Render(sf::RenderWindow& window) const;

		enum class eState
		{
			e_alive,
			e_dead,
			e_complete
		};

		eState GetState() const { return m_state; }
		sf::Vector2f GetPosition() const { return m_position; }
		sf::Vector2f GetMovementVector() const { return m_currentMovementVector; }



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
