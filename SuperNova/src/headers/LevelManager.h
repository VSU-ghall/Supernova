#pragma once
#include "Vector2.h"
#include "iostream"
#include <headers/TileMap.h>

static class LevelManager
{
	public:
		int numberOfLevels = 0;

		struct Level {
			LevelManager* levelManager;
			int* map;
			Vector2 startPosition;
			int levelNumber = (levelManager->numberOfLevels)++;
			int levelWidth = 20, levelHeight = 12;
		} testLevel = {this}, level1 = {this}, level2 = {this}, currentLevel = {this};

		LevelManager();
		Level getCurrentLevel();
		Level getLevel1();
		Level getLevel2();
		Level getTestLevel();
		TileMap getMap();
		void setLevel(Level level);

	private:
		static const int levelSize = 240;
		
		TileMap map;

		void init();
		void loadLevel(Level level);
};

