#include "Enemy.h"

#include "Constants.h"
#include "GlobalTime.h"
#include "Helpers.h"

td::Enemy::Enemy() :
	m_currentWaypointIndex(1),
	m_currentGoalPosition(constants::k_LEVEL_ONE_WAYPOINTS[m_currentWaypointIndex]),
	m_speed(100.f),
	m_position(-1000.f, 360.f),
	m_colour(239, 29, 231),
	m_visible(false),
	m_state(eState::e_alive)
{
	CalculateMovementVector();
}

td::Enemy::Enemy(const eEnemyType type) :
	m_currentWaypointIndex(1),
	m_currentGoalPosition(constants::k_LEVEL_ONE_WAYPOINTS[m_currentWaypointIndex]),
	m_speed(100.f),
	m_position(0.f, 360.f),
	m_visible(false),
	m_state(eState::e_alive)
{
	switch (type)
	{
	case eEnemyType::e_red:
		m_speed = 100.f;
		m_colour = sf::Color::Red;
		break;
	case eEnemyType::e_green:
		m_speed = 300.f;
		m_colour = sf::Color::Green;
		break;
	case eEnemyType::e_blue:
		m_speed = 150.f;
		m_colour = sf::Color::Blue;
		break;
	default: ;
	}


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
	const sf::Vector2f dxy = m_currentGoalPosition - m_position;

	// Check if it's overshot the waypoint
	if (helper_functions::definitely_greater_than(m_currentMovementVector.x, 0.f))
	{
		printf("I'm moving right\n");
		if (dxy.x < 0)
		{
			printf("I overshot my target!\n");
			m_position.x = m_currentGoalPosition.x;
		}
	}
	if (helper_functions::definitely_less_than(m_currentMovementVector.x, 0.f))
	{
		printf("I'm moving left\n");
		if (dxy.x > 0)
		{
			printf("I overshot my target!\n");
			m_position.x = m_currentGoalPosition.x;
		}
	}
	if (helper_functions::definitely_greater_than(m_currentMovementVector.y, 0.f))
	{
		printf("I'm moving down\n");
		if (dxy.y < 0)
		{
			printf("I overshot my target!\n");
			m_position.y = m_currentGoalPosition.y;
		}
	}
	if (helper_functions::definitely_less_than(m_currentMovementVector.y, 0.f))
	{
		printf("I'm moving up\n");
		if (dxy.y > 0)
		{
			printf("I overshot my target!\n");
			m_position.y = m_currentGoalPosition.y;
		}
	}



	const float mag = helper_functions::sqr_magnitude(dxy);

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
