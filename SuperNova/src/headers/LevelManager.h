#pragma once
#include "Vector2.h"
#include "iostream"
#include <headers/TileMap.h>
#include <headers/Sprite.h>
#include <vector>

static class LevelManager
{
	public:
		int numberOfLevels = 0;

		struct Level {
			LevelManager* levelManager;
			Sprite* background = NULL;
			bool hasBackground = false;
			int width = 20, height = 12, levelNumber = (levelManager->numberOfLevels)++;
			int* map;
			Vector2 startPosition;
			std::vector<std::vector<int>> colMap;

			int transitionTile;
			int collisionTile;
			int emptyTile;

			Level* left;
			Level* right;
			Level* top;
			Level* bot;

		} testLevel = {this}, 
			level1 = { this, new Sprite("src/resources/space_background_sprite_sheet.png", true, true, 4, 1280, 768, 1.0f, 1000), true },
			level2 = { this, new Sprite("src/resources/waterfall_background.png", true, false, 16, 350, 210, 4.57f, 500), true, 25, 17 },
			level3 = { this, new Sprite("src/resources/waterfall_background.png", true, false, 16, 350, 210, 5.49f, 500), true, 30, 16 },
			level4 = { this, new Sprite("src/resources/mining_background_1.png", true, false, 5, 200, 120, 6.46f, 500), true },
			level5 = { this, new Sprite("src/resources/space_background_sprite_sheet.png", true, true, 4, 1280, 768, 1.0f, 1000), true },
			currentLevel = {this};
		Level* currentLevelPtr;
		LevelManager();
		Sprite getCurrentBackground();
		Level getCurrentLevel();
		Level getLevel1();
		Level getLevel2();
		Level getLevel3();
		Level getLevel4();
		Level getLevel5();
		Level getTestLevel();
		TileMap getMap();
		void setLevel(Level level);

	private:
		TileMap map;

		void init();
		void loadLevel(Level* level);
};
