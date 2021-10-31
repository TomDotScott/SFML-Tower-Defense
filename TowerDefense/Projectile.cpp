#include "Projectile.h"

#include <SFML/Graphics/CircleShape.hpp>

#include "GlobalTime.h"
#include "Helpers.h"

td::Projectile::Projectile() :
	m_speed(0.f),
	m_lifetime(1.5f),
	m_active(false)
{
}

void td::Projectile::Init(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const float speed)
{
	m_position = startPosition;
	m_movementVector = helper_functions::normalise_vector(targetPosition - startPosition);
	m_speed = speed;
	// TODO: Replace the magic numbers
	m_lifetime = 1.5f;
	m_active = true;
}

void td::Projectile::Update()
{
	if (m_active)
	{
		m_position += m_movementVector * m_speed * GlobalTime::DeltaTime();

		m_lifetime -= GlobalTime::DeltaTime();
		if(m_lifetime < 0.f)
		{
			m_active = false;
		}
	}
}

void td::Projectile::Render(sf::RenderWindow& window) const
{
	if (m_active)
	{
		sf::CircleShape projectile{ 5.f };
		projectile.setFillColor(sf::Color::Magenta);
		projectile.setPosition(m_position);
		window.draw(projectile);
	}
}
