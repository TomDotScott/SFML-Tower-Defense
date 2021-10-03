#pragma once
#include <array>
#include <SFML/System/Vector2.hpp>

namespace td
{
	namespace constants
	{
		constexpr int k_screenWidth = 1280;
		constexpr int k_screenHeight = 720;

		constexpr float k_minDistance = 0.5f;

		const static std::array<sf::Vector2f, 10> LEVEL_ONE_WAYPOINTS {
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
}