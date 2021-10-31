#pragma once
#include <cmath>
#include <limits>

namespace td
{
	namespace helper_functions
	{
		inline float sqr_magnitude(const sf::Vector2f& v)
		{
			return v.x * v.x + v.y * v.y;
		}

		inline float magnitude(const sf::Vector2f& v)
		{
			return sqrtf(sqr_magnitude(v));
		}

		inline void normalise_vector(sf::Vector2f& v)
		{
			v /= magnitude(v);
		}

		inline sf::Vector2f normalise_vector(const sf::Vector2f& v)
		{
			const float mag = magnitude(v);
			return { v.x / mag, v.y / mag };
		}

		inline bool approximately_equal(const float a, const float b)
		{
			return std::fabs(a - b) <= ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * std::numeric_limits<float>::epsilon());
		}

		inline bool essentially_equal(const float a, const float b)
		{
			return std::fabs(a - b) <= ((std::fabs(a) > std::fabs(b) ? std::fabs(b) : std::fabs(a)) * std::numeric_limits<float>::epsilon());
		}

		inline bool definitely_greater_than(const float a, const float b)
		{
			return a - b > ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * std::numeric_limits<float>::epsilon());
		}

		inline bool definitely_less_than(const float a, const float b)
		{
			return b - a > ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * std::numeric_limits<float>::epsilon());
		}
	}
}
