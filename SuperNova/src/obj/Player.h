#pragma once
#include <SFML/Graphics.hpp>
class Player
{
	private:
		float x, y;
	public:
		float getX();
		float getY();

		void update();
		void draw(sf::RenderWindow& window);
		void checkMovment();
		void init();
};

