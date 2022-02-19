#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include <stdlib.h>

class Player
{
	private:
		float x, y;

	public:
		Vector2 startPosition;
		float getX();
		float getY();

		void draw(sf::RenderWindow& window);
		void checkMovement(std::vector<Vector2> vectors);
		void init();
		void respawn();
		void update(std::vector<Vector2> vectors);
		bool checkCollision(float velo, std::vector<Vector2> vectors);
};

