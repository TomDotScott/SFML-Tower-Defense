#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace td {
	class Projectile
	{
	public:
		Projectile();

		void Init(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, float speed);
		void Update();
		void Render(sf::RenderWindow& window) const;

		bool IsActive() const { return m_active; }

	private:
		sf::Vector2f m_position;
		sf::Vector2f m_movementVector;
		float m_speed;

		float m_lifetime;

		bool m_active;
	};
}