#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include <stdlib.h>
#include <headers/LevelManager.h>

class Player
{
	private:
		float x, y;

	public:
		Vector2 startPosition;
		float getX();
		float getY();

		void draw(sf::RenderWindow& window);
		void checkMovement(std::vector<Vector2> vectors, LevelManager::Level currentLevel);
		void init();
		void respawn();
		void update(std::vector<Vector2> vectors, LevelManager::Level currentLevel);
		bool checkCollision(float velo, std::vector<Vector2> vectors, LevelManager::Level currentLevel);
};

