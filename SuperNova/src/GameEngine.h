#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <iostream>
#include "../src/objects/Player.h"
#include "../src/objects/TileMap.h"

class GameEngine
{
private:
	Player player;
	TileMap map;
	const int tileSize = 64;
	int levelWidth = 20, levelHeight = 12;
	float windowWidth = tileSize * levelWidth, windowHeight = tileSize * levelHeight;
	// creates global window
	sf::RenderWindow window;
	sf::View view;

public:
	GameEngine();
	void run();
	void init();
	void draw();
	void update();
	void drawGrid();
	sf::View getViewport(float width, float height);
};



