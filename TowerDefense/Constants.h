#pragma once
#include <array>
#include <SFML/System/Vector2.hpp>

namespace td::constants
{
	constexpr int k_SCREEN_WIDTH = 1280;
	constexpr int k_SCREEN_HEIGHT = 720;

	constexpr float k_TIME_BETWEEN_SPAWN = 1.5f;
	constexpr int k_MAX_WAVES = 3;

	constexpr float k_MIN_DISTANCE = 0.5f;

	constexpr float k_PROJECTILE_SPEED = 200.f;
	constexpr int k_PROJECTILE_DAMAGE = 50;
	constexpr float k_ENEMY_SIZE = 64.f;

	const static std::array<sf::Vector2f, 10> k_LEVEL_ONE_WAYPOINTS {
		sf::Vector2f(0.f, 360.f),
		sf::Vector2f(300.f, 360.f),
		sf::Vector2f(300.f, 135.f),
		sf::Vector2f(575.f, 135.f),
		sf::Vector2f(575.f, 610.f),
		sf::Vector2f(865.f, 610.f),
		sf::Vector2f(865.f, 125.f),
		sf::Vector2f(1105.f, 125.f),
		sf::Vector2f(1105.f, 360.f),
		sf::Vector2f(1323.f, 360.f)
	};
}
