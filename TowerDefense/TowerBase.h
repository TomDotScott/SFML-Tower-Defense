#pragma once
#include <SFML/Graphics/RenderWindow.hpp>


namespace td {
	// The base class for all towers in the game
	class TowerBase
	{
	public:
		explicit TowerBase(const sf::Vector2f& position);
		virtual void Update();
		virtual void Render(sf::RenderWindow& window) const;


	private:
		float m_rangeRadius;
		sf::Vector2f m_position;

	};
}
