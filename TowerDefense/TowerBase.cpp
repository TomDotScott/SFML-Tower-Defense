#include "TowerBase.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

td::TowerBase::TowerBase(const sf::Vector2f& position) :
	m_rangeRadius(128.f),
	m_position(position)
{

}

void td::TowerBase::Update()
{
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
}
