#include "Enemy.h"

#include "Constants.h"
#include "GlobalTime.h"
#include "Helpers.h"

td::Enemy::Enemy() :
	m_currentWaypointIndex(1),
	m_currentGoalPosition(td::constants::k_LEVEL_ONE_WAYPOINTS[m_currentWaypointIndex]),
	m_speed(100.f),
	m_position(-1000.f, 360.f),
	m_colour(239, 29, 231),
	m_visible(false),
	m_state(eState::e_alive)
{
	CalculateMovementVector();
}

td::Enemy::Enemy(const sf::Color colour) :
	m_currentWaypointIndex(1),
	m_currentGoalPosition(td::constants::k_LEVEL_ONE_WAYPOINTS[m_currentWaypointIndex]),
	m_speed(100.f),
	m_position(0.f, 360.f),
	m_colour(colour),
	m_visible(false),
	m_state(eState::e_alive)
{
	CalculateMovementVector();
}

void td::Enemy::Update()
{
	if (m_visible && m_state == eState::e_alive) {
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
		rect.setFillColor(m_colour);
		rect.setPosition(m_position);
		window.draw(rect);
	}
}

void td::Enemy::Spawn()
{
	m_visible = true;
}

void td::Enemy::Move()
{
	// Move the automaton
	m_position += m_currentMovementVector * m_speed * GlobalTime::DeltaTime();
}

void td::Enemy::CheckWaypoints()
{
	const sf::Vector2f hereToGoalPosition = m_currentGoalPosition - m_position;

	const float mag = helper_functions::sqr_magnitude(hereToGoalPosition);

	if (helper_functions::definitely_less_than(mag, constants::k_MIN_DISTANCE * constants::k_MIN_DISTANCE))
	{
		if (m_currentWaypointIndex < static_cast<int>(constants::k_LEVEL_ONE_WAYPOINTS.size() - 1))
		{
			m_currentGoalPosition = constants::k_LEVEL_ONE_WAYPOINTS[++m_currentWaypointIndex];

			CalculateMovementVector();
		}
		else
		{
			m_visible = false;
			m_state = eState::e_complete;
		}
	}
}

void td::Enemy::CalculateMovementVector()
{

	sf::Vector2f ab = m_currentGoalPosition - m_position;

	helper_functions::normalise_vector(ab);

	m_currentMovementVector = ab;
}
