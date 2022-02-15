#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "headers/Player.h"
#include "headers/TileMap.h"
#include "LevelManager.h"

class GameEngine
{
private:
	Player player;
	TileMap map;
	const int tileSize = 64;
	int levelWidth = 20, levelHeight = 12;
	float windowWidth = tileSize * levelWidth, windowHeight = tileSize * levelHeight;
	LevelManager levelManager;

	// creates global window
	sf::RenderWindow window;
	sf::View view;
	sf::Music music;

public:
	GameEngine();
	void run();
	void init();
	void draw();
	void update();
	void drawGrid();
	void playMusic();
	sf::View getViewport(float width, float height);
};



