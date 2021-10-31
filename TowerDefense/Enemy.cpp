#include "Enemy.h"

#include "Constants.h"
#include "GlobalTime.h"
#include "Helpers.h"

td::Enemy::Enemy() :
	m_currentWaypointIndex(1),
	m_currentGoalPosition(constants::k_LEVEL_ONE_WAYPOINTS[m_currentWaypointIndex]),
	m_stats(k_RED_STATS),
	m_position(-1000.f, 360.f),
	m_visible(false),
	m_state(eState::e_alive)
{
	CalculateMovementVector();
}

td::Enemy::Enemy(const eEnemyType type) :
	m_currentWaypointIndex(1),
	m_currentGoalPosition(constants::k_LEVEL_ONE_WAYPOINTS[m_currentWaypointIndex]),
	m_stats(k_RED_STATS),
	m_position(0.f, 360.f),
	m_visible(false),
	m_state(eState::e_alive)
{
	switch (type)
	{
	case eEnemyType::e_red:
		m_stats = k_RED_STATS;
		break;
	case eEnemyType::e_green:
		m_stats = k_GREEN_STATS;
		break;
	case eEnemyType::e_blue:
		m_stats = k_BLUE_STATS;
		break;
	default:;
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
		sf::RectangleShape rect({ constants::k_ENEMY_SIZE, constants::k_ENEMY_SIZE });
		rect.setOrigin(32, 32);

		switch (m_stats.m_Type) {
		case eEnemyType::e_red:
			rect.setFillColor(sf::Color::Red);
			break;
		case eEnemyType::e_green:
			rect.setFillColor(sf::Color::Green);
			break;
		case eEnemyType::e_blue:
			rect.setFillColor(sf::Color::Blue);
			break;
		default:;
		}

		rect.setPosition(m_position);
		window.draw(rect);
	}
}

void td::Enemy::TakeDamage(const int dmgAmount)
{
	m_stats.m_Health -= dmgAmount;
	if (m_stats.m_Health <= 0)
	{
		switch (m_stats.m_Type) {
			case eEnemyType::e_red: 
				m_visible = false;
				m_state = eState::e_dead;
			break;
		case eEnemyType::e_green: 
			// Turn blue
			m_stats = k_BLUE_STATS;
			break;
		case eEnemyType::e_blue: 
			m_stats = k_RED_STATS;
			break;
		default: 
			printf("UNKNOWN ENEMY TYPE\n");
			break;
		}
	}
}

void td::Enemy::Spawn()
{
	m_visible = true;
}

void td::Enemy::Move()
{
	// Move the automaton
	m_position += m_currentMovementVector * m_stats.m_Speed * GlobalTime::DeltaTime();
}

void td::Enemy::CheckWaypoints()
{
	const sf::Vector2f dxy = m_currentGoalPosition - m_position;

	// Check if it's overshot the waypoint
	if (helper_functions::definitely_greater_than(m_currentMovementVector.x, 0.f))
	{
		if (dxy.x < 0)
		{
			m_position.x = m_currentGoalPosition.x;
		}
	}
	if (helper_functions::definitely_less_than(m_currentMovementVector.x, 0.f))
	{
		if (dxy.x > 0)
		{
			m_position.x = m_currentGoalPosition.x;
		}
	}
	if (helper_functions::definitely_greater_than(m_currentMovementVector.y, 0.f))
	{
		if (dxy.y < 0)
		{
			m_position.y = m_currentGoalPosition.y;
		}
	}
	if (helper_functions::definitely_less_than(m_currentMovementVector.y, 0.f))
	{
		if (dxy.y > 0)
		{
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
