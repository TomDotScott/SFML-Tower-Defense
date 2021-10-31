#pragma once
#include <list>
#include <queue>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Projectile.h"


namespace td {
	// The base class for all towers in the game
	class TowerBase
	{
	public:
		explicit TowerBase(const sf::Vector2f& position);
		virtual ~TowerBase() = default;
		virtual void Update();
		virtual void Render(sf::RenderWindow& window) const;

		// TODO: Change this to GetActiveProjectiles
		std::list<Projectile>& GetProjectiles();

		float GetRadius() const { return m_rangeRadius; }
		sf::Vector2f GetPosition() const { return m_position; }

		bool IsPointInsideRadius(sf::Vector2f position) const;
		void AddTarget(const sf::Vector2f& position);

	private:
		float m_rangeRadius;
		sf::Vector2f m_position;
		float m_shotCooldown;

		std::queue<sf::Vector2f> m_enemyTargetPositions;
		std::list<Projectile> m_projectilePool;

		void Shoot();
	};
}
