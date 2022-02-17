#include "headers/GameEngine.h"

GameEngine::GameEngine() 
	:window(sf::VideoMode(windowWidth, windowHeight), "SuperNova")
{
	
}

void GameEngine::run() {

	init();

	// main loop --> continues each frame while window is open
	while (window.isOpen()) {

		// event handling
		sf::Event event;
		while (window.pollEvent(event))
			handleEvent(event);

		update();
		draw();
	}
}

//
//	Initializes the game components
//
void GameEngine::init() {
	view.setSize(windowWidth, windowHeight);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	view = getViewport(windowWidth, windowHeight);
	window.setFramerateLimit(60);

	loadLevel(levelManager.getLevel1());
	player.init();

	playMusic();
}

//
// Draws all objects on window
//
void GameEngine::draw() {
	window.clear();

	window.setView(view);
	window.draw(levelManager.getMap());

	//drawGrid();

	player.draw(window);

	window.display();
}

//
// Draws grid for development/testing purposes
//
void GameEngine::drawGrid() {
	for (int x = 0; x <= window.getSize().x; x = x + tileSize) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(x, 0);
		lines[0].color = sf::Color::White;
		lines[1].position = sf::Vector2f(x, window.getSize().y);
		lines[1].color = sf::Color::White;

		window.draw(lines);
	}

	for (int y = 0; y <= window.getSize().y; y = y + tileSize) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(0, y);
		lines[0].color = sf::Color::White;
		lines[1].position = sf::Vector2f(window.getSize().x, y);
		lines[1].color = sf::Color::White;

		window.draw(lines);
	}
}

//
// Sets viewport to keep game aspect ratio
// ** Adapted from official SFML wiki (src: https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view)
//
sf::View GameEngine::getViewport(float width, float height) {
	float windowRatio = width / height;
	float viewRatio = windowWidth / windowHeight;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	// If horizontalSpacing is true, the black bars will appear on the left and right side.
	// Otherwise, the black bars will appear on the top and bottom.

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}
	else {
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

	return view;
}

//
// Handles all our games' events
//
void GameEngine::handleEvent(sf::Event event) {
	// event triggered when window is closed
	if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();

	// sets viewport when window is resized
	if (event.type == sf::Event::Resized)
		view = getViewport(event.size.width, event.size.height);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (levelManager.getCurrentLevel().levelNumber == 1) {
			loadLevel(levelManager.getLevel2());
			std::cout << "LEVEL 2" << std::endl;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (levelManager.getCurrentLevel().levelNumber == 2) {
			loadLevel(levelManager.getLevel1());
			std::cout << "LEVEL 1" << std::endl;
		}
	}
		
}

//
// Loads level from LevelManager
//
void GameEngine::loadLevel(LevelManager::Level level) {
	player.startPosition = Vector2(level.startPosition);
	player.respawn();
	levelManager.setLevel(level);
}

//
// Adding background sound to the game
// ** Using code from url: https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Music.php
//
void GameEngine::playMusic()
{
	// Open the Background Music
	if (!music.openFromFile("src/resources/background_music.wav")) {
		std::cout << "Could not load background_music" << std::endl;
		return;
	}

	music.setVolume(25);

	music.setLoop(true);         // make it loop
	// Play it
	music.play();
}

//
// Updates all game objects
//
void GameEngine::update() {
	player.update();
}