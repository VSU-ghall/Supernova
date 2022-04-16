#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <iostream>
#include "headers/Player.h"
#include "headers/TileMap.h"
#include "headers/LevelManager.h"
#include "headers/Sprite.h"
#include "headers/EntityManager.h"
#include "headers/StoryManager.h"

class GameEngine
{
private:
	Player player;
	LevelManager levelManager;
	StoryManager storyManager;
	const int tileSize = 64;
	float viewWidth, viewHeight;
	bool scenePlaying = false, displayingText = false;

	// creates global window
	sf::RenderWindow gameWindow, menuWindow;
	sf::View view;
	sf::Music music, soundEffect;
	Sprite *btnMenu = new Sprite("src/resources/MenuButton.png"),
		*pixiguide = new Sprite("src/resources/pixiguide.png", true, false, 6, 32, 48, 1.0f, 150),
		*btnPlay = new Sprite("src/resources/MenuPlayButton.png"),
		*btnOptions = new Sprite("src/resources/MenuOptionsButton.png"),
		*btnExit = new Sprite("src/resources/MenuExitButton.png");
	sf::Texture backgroundTexture;
	sf::RectangleShape gameBar, chatBar, blackRect, hpBarBack, hpBarInside, jetPackInside, jetPackBack, gameOverBackground, gameOver;
	sf::Texture gameOverText;
	sf::Vector2f pixiLocation;


	enum Mode {menu, game, paused};
	Mode gameMode;

	EntityManager enemies;

public:
	GameEngine();

	LevelManager* getLevelManager() { return &levelManager; }
	Player* getPlayer() { return &player; };
	sf::RenderWindow* getWindow() { return &gameWindow; }

	void run();
	void init();
	void initGame();
	void initMenu();
	void drawGame();
	void drawGrid();
	void drawMenu();
	sf::View getViewport(float width, float height);
	void handleEvent(sf::Event event);
	void loadLevel(LevelManager::Level level, Vector2 startp);
	void playMusic();
	void playSoundEffect(const std::string& filePath);
	void setWindowView(sf::RenderWindow &window, float width, float height);
	void updateGame();
	void updateMenu();
	sf::Vector2f updatePixi();


	void addEntities();
	void updateComponentView();
	void updateHpBar();
	void updateJetPackBar();
	void initJetPackBar();
};