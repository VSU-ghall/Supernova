#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <iostream>


//Tile map code was taken off an example in the SFML documentation https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
//we are using a base class of drawable. This is the base class to all drawable objects in SFML and this allows us to have more consistent optimization.
//adding the baseclass of transformable allows easy access too the same trasfomation classes (like setPostion, setRotation,move...ect);
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};