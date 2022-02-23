#include "headers/LevelManager.h"


LevelManager::LevelManager(){
	init();
}

void LevelManager::init() {
	testLevel.map = new int[testLevel.width * testLevel.height] {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
		testLevel.startPosition = Vector2(5, 11);


	level1.map = new int[level1.width * level1.height] {
		 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
		 3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,	 3,  3,  3,  3,  3,  3,  3,
		17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
		19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
		 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  0,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  6,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		 6,  6,  6,  6,  6,  6,  6,  4,  4,  4,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
		 4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
		 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
	};
		level1.startPosition = Vector2(5, 9);

	level2.map = new int[level2.width * level2.height] {
		 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
		 3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
		17, 17, 17, 17, 27, 23, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 26, 17, 17, 17, 17,
		17, 17, 17, 27, 28, 29,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 25, 26, 17, 17, 17,
		17, 17, 27, 28, 29,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 25, 26, 17, 17,
		17, 27, 28, 29,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 25, 26, 17,
		27, 28, 29,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 25, 26,
		28, 29,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 25,
		29,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24,
		 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		 8,  8,  8,  8,  8,  8,  8,  8,  5,  6,  6,  6,  6,  6,  6,  6,  7,  8,  8,  8,  8,  8,  8,  8,  8,
		 4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
		 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
		 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
		 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
		 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	};
		level2.startPosition = Vector2(15, 11);
		level2.background->sprite.setTextureRect(sf::IntRect(0, 0, 64*level2.width, 64*level2.height));
}

Sprite LevelManager::getCurrentBackground() {
	return *currentLevel.background;
}

LevelManager::Level LevelManager::getCurrentLevel() {
	return currentLevel;
}

LevelManager::Level LevelManager::getLevel1() {
	return LevelManager::level1;
}

LevelManager::Level LevelManager::getLevel2() {
	return LevelManager::level2;
}

LevelManager::Level LevelManager::getTestLevel() {
	return LevelManager::testLevel;
}

TileMap LevelManager::getMap() {
	return map;
}

void LevelManager::loadLevel(Level* level) {
	// create the tilemap from the level definition
	if (!map.load("src/resources/tilemap_v2.png", sf::Vector2u(64, 64), level->map, level->width, level->height))
		std::cout << "Error loading TileMap";

	level->colMap = map.loadColMap(level->map, level->width, level->height);

	if (level->hasBackground)
		level->background->animating = true;
}

void LevelManager::setLevel(Level level) {
	if (currentLevel.hasBackground && currentLevel.background->animating)
		currentLevel.background->animating = false;

	currentLevel = level;
	loadLevel(&currentLevel);
}