#pragma once
#include <SFML/Graphics.hpp>

namespace td {

	// TODO: Expand functionality to read levels from TILED projects
	class Level
	{
	public:
		Level();
		void Render(sf::RenderWindow& window) const;

	private:
		// TODO: Eliminate this, and use the texture system that I'm yet to implement
		sf::Texture m_backgroundTexture;
		sf::Sprite m_backgroundSprite;
	};
}