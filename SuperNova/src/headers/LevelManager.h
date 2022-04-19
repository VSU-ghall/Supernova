#pragma once
#include "Vector2.h"
#include "iostream"
#include <array>
#include <headers/TileMap.h>
#include <headers/Sprite.h>
#include <vector>
#include <headers/Entity.h>
#include <headers/Object.h>

static class LevelManager
{
	public:
		int numberOfLevels = 0;
		std::vector<Object*> icons;

		struct Level {
			LevelManager* levelManager;
			Sprite* background = NULL;
			bool hasBackground = false;
			int width = 20, height = 12, levelNumber = (levelManager->numberOfLevels)++;
			int* map;
			Vector2 leftStartPosition;
			Vector2 rightStartPosition;
			Vector2 botStartPosition;
			Vector2 topStartPosition;
			std::vector<std::vector<int>> colMap;

			int breakableNum;
			int collisionTile;
			int emptyTile;

			Level* left;
			Level* right;
			Level* top;
			Level* bot;

			std::vector<Entity> enemies;
			std::vector<Object*> objects;
			std::string levelName;

		} testLevel = {this}, 
			level1  = { this, new Sprite("src/resources/space_background_sprite_sheet.png", true, true, 4, 1280, 768, 1.0f, 1000), true },
			level2  = { this, new Sprite("src/resources/waterfall_background.png", true, false, 16, 350, 210, 4.57f, 500), true, 25, 17 },
			level3  = { this, new Sprite("src/resources/waterfall_background.png", true, false, 16, 350, 210, 5.49f, 500), true, 30, 16 },
			level4  = { this, new Sprite("src/resources/mining_background_1.png", true, false, 5, 200, 120, 6.4f, 500), true },
			level5  = { this, new Sprite("src/resources/space_background_sprite_sheet.png", true, true, 4, 1280, 768, 1.05f, 1000), true, 21, 12 },
			level6  = { this, new Sprite("src/resources/mining_background_1.png", true, false, 5, 200, 120, 9.65f, 500), true, 30, 16 },
			level7  = { this, new Sprite("src/resources/mining_background_4.png", false, false, 1, 768, 1920, 1.f, 1), true, 12, 30 },
			level8  = { this, new Sprite("src/resources/mining_background_2.png", true, false, 8, 200, 120, 9.6f, 500), true, 30, 9 },
			level9  = { this, new Sprite("src/resources/mining_background_3.png", true, false, 5, 200, 120, 9.6f, 500), true, 30, 12 },
			level10 = { this, new Sprite("src/resources/mining_background_3.png", true, false, 5, 200, 120, 9.6f, 500), true, 30, 12 },
			level11 = { this, new Sprite("src/resources/waterfall_background.png", true, false, 16, 350, 210, 5.49f, 500), true, 30, 16 },
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
		Level getLevel6();
		Level getLevel7();
		Level getLevel8();
		Level getLevel9();
		Level getLevel10();
		Level getLevel11();
		Level getTestLevel();
		TileMap getMap();
		void removeItem(Level level, Object item);
		void setLevel(Level level);
		std::vector<Level> getAllLevels();

	private:
		TileMap map;

		void init();
		void loadLevel(Level* level);

		void addEntity(Sprite* sprite, Level* level, sf::Vector2f position);
		void addEntity(Sprite* sprite, Level* level, sf::Vector2f position, sf::Vector2f position2);
		void addIconObject(Sprite* sprite, Level* level, sf::Vector2f position);
		void addHealthPack(Level* level, sf::Vector2f position);

		Sprite* getBigScorpion();
		Sprite* getDashBoots();
		Sprite* getDrill();
		Sprite* getHealthPack();
		Sprite* getJetpack();
		Sprite* getMiningBot();
		Sprite* getScorpion();
		Sprite* getSpicyFlower();
		Sprite* getSpikes();
		Sprite* getSpikesUpsideDown();

		std::vector<Level> allLevels;
};
