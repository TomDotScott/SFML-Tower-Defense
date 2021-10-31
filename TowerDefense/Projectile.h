#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace td {
	class Projectile
	{
	public:
		Projectile();

		void Init(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, int damage, float speed);
		void Update();
		void Render(sf::RenderWindow& window) const;

		sf::Vector2f GetPosition() const { return m_position; }

		bool IsActive() const { return m_active; }
		void SetActive(const bool activeState) { m_active = activeState; }
		int GetDamage() const { return m_damage; }

	private:
		sf::Vector2f m_position;
		sf::Vector2f m_movementVector;
		float m_speed;
		int m_damage;

		float m_lifetime;

		bool m_active;
	};
}