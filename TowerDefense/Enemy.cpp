#include "Enemy.h"

#include "Constants.h"
#include "GlobalTime.h"
#include "Helpers.h"

td::Enemy::Enemy() :
	m_currentWaypointIndex(1),
	m_currentGoalPosition(td::constants::LEVEL_ONE_WAYPOINTS[m_currentWaypointIndex]),
	m_currentMovementVector({ 1.f, 0.f }),
	m_speed(100.f),
	m_position(0.f, 360.f),
	m_visible(true)
{
}

void td::Enemy::Update()
{
	if (m_visible) {
		Move();

		// See if it's hit its goal
		CheckWaypoints();
	}
}

void td::Enemy::Render(sf::RenderWindow& window) const
{
	if (m_visible) {
		sf::RectangleShape rect({ 64.f, 64.f });
		rect.setOrigin(32, 32);
		rect.setFillColor(sf::Color::Red);
		rect.setPosition(m_position);
		window.draw(rect);
	}
}

void td::Enemy::Move()
{
	// Move the automaton
	m_position += m_currentMovementVector * m_speed * GlobalTime::DeltaTime();
}

void td::Enemy::CheckWaypoints()
{
	sf::Vector2f ab = m_currentGoalPosition - m_position;

	const float mag = helper_functions::sqr_magnitude(ab);

	if (helper_functions::definitely_less_than(mag, constants::k_minDistance * constants::k_minDistance))
	{
		if (m_currentWaypointIndex < static_cast<int>(constants::LEVEL_ONE_WAYPOINTS.size() - 1))
		{
			m_currentGoalPosition = constants::LEVEL_ONE_WAYPOINTS[++m_currentWaypointIndex];

			ab = m_currentGoalPosition - m_position;

			helper_functions::normalise_vector(ab);

			m_currentMovementVector = ab;
		}
		else
		{
			m_visible = false;
		}
	}




}
