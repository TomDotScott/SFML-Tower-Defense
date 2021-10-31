#include "TowerBase.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Constants.h"
#include "GlobalTime.h"

td::TowerBase::TowerBase(const sf::Vector2f& position) :
	m_rangeRadius(128.f),
	m_position(position),
	m_shotCooldown(0.1f)
{

}

void td::TowerBase::Update()
{
	m_shotCooldown -= GlobalTime::DeltaTime();

	if(m_shotCooldown < 0.f)
	{
		if(!m_enemyTargetPositions.empty())
		{
			Shoot();
			m_shotCooldown = 0.1f;
		}
	}

	// Update any active projectiles
	for (auto& projectile : m_projectilePool)
	{
		if (projectile.IsActive())
		{
			projectile.Update();
		}
	}
	while (!m_enemyTargetPositions.empty()) m_enemyTargetPositions.pop();
}

void td::TowerBase::Render(sf::RenderWindow& window) const
{
	// Draw the radius
	sf::CircleShape radius(m_rangeRadius);
	radius.setFillColor({ 128, 128, 128, 128 });
	radius.setOrigin(radius.getGlobalBounds().width / 2, radius.getGlobalBounds().height / 2);
	radius.setPosition(m_position);
	window.draw(radius);

	// Draw the tower
	sf::RectangleShape tower({ 64.f, 64.f });
	tower.setOrigin(tower.getGlobalBounds().width / 2, tower.getGlobalBounds().height / 2);
	tower.setPosition(m_position);
	window.draw(tower);

	// Render any active projectiles
	for(auto& projectile : m_projectilePool)
	{
		if(projectile.IsActive())
		{
			projectile.Render(window);
		}
	}
}

bool td::TowerBase::IsPointInsideRadius(const sf::Vector2f position) const
{
	const sf::Vector2f dxy = position - m_position;
	return std::powf(dxy.x, 2) + std::powf(dxy.y, 2) <= std::powf(m_rangeRadius, 2);
}

void td::TowerBase::AddTarget(const sf::Vector2f& position)
{
	m_enemyTargetPositions.push(position);
}

void td::TowerBase::Shoot()
{
	// TODO: Have different targetting modes; First, Last, Close, Strongest
	// If the list is empty then construct a projectile and shoot
	if(m_projectilePool.empty())
	{
		m_projectilePool.emplace_back();
		m_projectilePool.back().Init(m_position, m_enemyTargetPositions.front(), constants::k_PROJECTILE_SPEED);
	}
	else {
		// Find the first inactive projectile
		Projectile* inactiveProj = nullptr;
		for (auto& proj : m_projectilePool)
		{
			if (!proj.IsActive())
			{
				inactiveProj = &proj;
				break;
			}
		}

		if (inactiveProj) {
			inactiveProj->Init(m_position, m_enemyTargetPositions.front(), constants::k_PROJECTILE_SPEED);
		}else
		{
			// If all the projectiles are active, then we need to create a new one to shoot
			m_projectilePool.emplace_back();
			m_projectilePool.back().Init(m_position, m_enemyTargetPositions.front(), constants::k_PROJECTILE_SPEED);
		}
	}
}
