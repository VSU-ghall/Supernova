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
	LevelManager levelManager;
	const int tileSize = 64;
	float windowWidth, windowHeight;

	// creates global window
	sf::RenderWindow window;
	sf::View view;
	sf::Music music;
	sf::Sprite background;
	sf::Texture texture;
	std::vector<Vector2> levelVector;

public:
	GameEngine();
	void run();
	void init();
	void draw();
	void drawGrid();
	sf::View getViewport(float width, float height);
	void handleEvent(sf::Event event);
	void loadLevel(LevelManager::Level level);
	void playMusic();
	void update();
};



