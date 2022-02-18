#pragma once
#include "Vector2.h"
#include "iostream"
#include <headers/TileMap.h>
#include <headers/SpriteManager.h>


static class LevelManager
{
	public:
		int numberOfLevels = 0;

		struct Level {
			LevelManager* levelManager;
			int width = 20, height = 12, levelNumber = (levelManager->numberOfLevels)++;
			int* map;
			Vector2 startPosition;
			sf::Sprite background;
			sf::Texture texture;
			bool hasBackground = false;
		} testLevel = {this}, level1 = {this}, level2 = {this, 25, 17}, currentLevel = {this};

		LevelManager(SpriteManager spriteManager);
		Level getCurrentLevel();
		Level getLevel1();
		Level getLevel2();
		Level getTestLevel();
		TileMap getMap();
		void setLevel(Level level);

	private:
		TileMap map;
		SpriteManager spriteManager;

		void init();
		void loadLevel(Level level);
};

