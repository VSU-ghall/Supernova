#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Player
{
	private:
		float x, y;

	public:
		Vector2 startPosition;
		float getX();
		float getY();

		void update();
		void draw(sf::RenderWindow& window);
		void checkMovement();
		void init();
};

