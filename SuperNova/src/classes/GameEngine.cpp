#include "headers/GameEngine.h"

GameEngine::GameEngine() 
	:gameWindow(sf::VideoMode(), "SuperNova"), menuWindow(sf::VideoMode(), "SuperNova - Menu"), storyManager(&gameWindow, &scenePlaying)
{}

void GameEngine::run() {
	init();

	// main loop --> continues each frame while window is open
	while (gameWindow.isOpen() && menuWindow.isOpen()) {
		if (scenePlaying) gameMode = scene;
		//else gameMode = game;

		// event handling
		sf::Event event;
		if (gameMode == menu)
			while (menuWindow.pollEvent(event))
				handleEvent(event);
		else
			while (gameWindow.pollEvent(event))
				handleEvent(event);

		switch (gameMode) {
			case menu:
				updateMenu();
				drawMenu();
				std::cout << "menu" << std::endl; break;
			case scene:
				updateGame();
				drawGame();
				std::cout << "scene" << std::endl; break;
			case game:
				updateGame();
				drawGame();
				std::cout << "game" << std::endl; break;
		}
		
	}
}

//
//	Initializes the game components
//
void GameEngine::init() {
	initMenu();

	playMusic();

	//storyManager.playLogoIntro();
	//initGame();
}

void GameEngine::initGame() {
	gameWindow.setFramerateLimit(60);

	loadLevel(levelManager.getLevel1());
	player.init();

	gamebar.setFillColor(sf::Color(59, 30, 11));
	btnLevel1->getSprite()->setTextureRect(sf::IntRect(0, 0, 150, 65));
	btnLevel2->getSprite()->setTextureRect(sf::IntRect(0, 0, 150, 65));

	gameWindow.setVisible(true);
	gameMode = game;
}

void GameEngine::initMenu() {
	blackRect.setFillColor(sf::Color(0, 10, 0, 255));
	menuWindow.setFramerateLimit(60);
	setWindowView(menuWindow, tileSize * 20, tileSize * 20);

	// All menu buttons are centered and linked together, so if you vertically move the first, the others with it.
	btnPlay->getSprite()->setTextureRect(sf::IntRect(0, 0, 256, 75));
	btnPlay->getSprite()->setPosition((menuWindow.getSize().x - 256) / 2, (menuWindow.getSize().y - 74*5) / 2);
	
	btnOptions->getSprite()->setTextureRect(sf::IntRect(0, 0, 448, 75));
	btnOptions->getSprite()->setPosition((menuWindow.getSize().x - 448) / 2, btnPlay->getSprite()->getPosition().y + (74*2));
	
	btnExit->getSprite()->setTextureRect(sf::IntRect(0, 0, 254, 75));
	btnExit->getSprite()->setPosition((menuWindow.getSize().x - 254) / 2, btnOptions->getSprite()->getPosition().y + (74 * 2));
}

//
// Draws all objects on game window
//
void GameEngine::drawGame() {
	gameWindow.clear();

	gameWindow.setView(view);

	if (levelManager.currentLevel.hasBackground) {
		gameWindow.draw(*levelManager.getCurrentBackground().getSprite());
	}

	gameWindow.draw(levelManager.getMap());

	//drawGrid();

	if (gameMode != scene) player.draw(gameWindow);
	gameWindow.draw(*pixiguide->getSprite());

	gameWindow.draw(gamebar);
	gameWindow.draw(*btnLevel1->getSprite()); gameWindow.draw(*btnLevel2->getSprite());

	if (gameMode == scene) storyManager.draw();

	gameWindow.display();
}

//
// Draws grid for development/testing purposes
//
void GameEngine::drawGrid() {
	for (int x = 0; x <= gameWindow.getSize().x; x = x + tileSize) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(x, 0);
		lines[0].color = sf::Color::White;
		lines[1].position = sf::Vector2f(x, gameWindow.getSize().y);
		lines[1].color = sf::Color::White;

		gameWindow.draw(lines);
	}

	for (int y = 0; y <= gameWindow.getSize().y; y = y + tileSize) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(0, y);
		lines[0].color = sf::Color::White;
		lines[1].position = sf::Vector2f(gameWindow.getSize().x, y);
		lines[1].color = sf::Color::White;

		gameWindow.draw(lines);
	}
}

//
// Draws all objects on menu window
//
void GameEngine::drawMenu() {
	menuWindow.clear();
	menuWindow.setView(view);
	
	menuWindow.draw(blackRect);

	menuWindow.draw(*btnPlay->getSprite());
	menuWindow.draw(*btnOptions->getSprite());
	menuWindow.draw(*btnExit->getSprite());

	menuWindow.display();
}

//
// Sets viewport to keep game aspect ratio
// ** Adapted from official SFML wiki (src: https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view)
//
sf::View GameEngine::getViewport(float width, float height) {
	float windowRatio = width / height;
	float viewRatio = viewWidth / viewHeight;
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
		if (gameMode == game || gameMode == scene) gameWindow.close();
		else if (gameMode == menu) menuWindow.close();

	// sets viewport when window is resized
	if (event.type == sf::Event::Resized) {
		view = getViewport(event.size.width, event.size.height);
		gamebar.setSize(sf::Vector2f(event.size.width, 75));
		btnLevel1->getSprite()->setPosition(gamebar.getPosition().x + 10, gamebar.getPosition().y + 5);
		btnLevel2->getSprite()->setPosition(gamebar.getPosition().x + 20 + btnLevel1->getTexture().getSize().x-150, gamebar.getPosition().y + 5);
	}

	if (event.type == sf::Event::KeyReleased) {
		if (sf::Keyboard::D || sf::Keyboard::A)
			if (player.stoppedLeft || player.stoppedRight)
				player.moving = false;
	}

	if (player.transitioning) {
		std::cout << levelManager.getCurrentLevel().levelNumber << std::endl;
		if (levelManager.getCurrentLevel().levelNumber == 2) {
			loadLevel(levelManager.getLevel1());
			player.transitioning = false;
		}
		else if (levelManager.getCurrentLevel().levelNumber == 1) {
			loadLevel(levelManager.getLevel2());
			player.transitioning = false;
		}
	}

	// Check if game Level 1 Button is clicked
	sf::Vector2i pixelPos = sf::Mouse::getPosition(gameWindow);
	sf::Vector2f worldPos = gameWindow.mapPixelToCoords(pixelPos);
	if (gameMode == game && btnLevel1->getSprite()->getGlobalBounds().contains(worldPos.x, worldPos.y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnLevel1->getSprite()->setTextureRect(sf::IntRect(150, 0, 150, 65));
		if (event.type == sf::Event::MouseButtonReleased) {
			if (levelManager.getCurrentLevel().levelNumber == 2)
				loadLevel(levelManager.getLevel1());
			btnLevel1->getSprite()->setTextureRect(sf::IntRect(0, 0, 150, 65));
		}
	}

	// Check if game Level 2 Button is clicked
	if (gameMode == game && btnLevel2->getSprite()->getGlobalBounds().contains(worldPos.x, worldPos.y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnLevel2->getSprite()->setTextureRect(sf::IntRect(150, 0, 150, 65));
		if (event.type == sf::Event::MouseButtonReleased) {
			if (levelManager.getCurrentLevel().levelNumber == 1)
				loadLevel(levelManager.getLevel2());
			btnLevel2->getSprite()->setTextureRect(sf::IntRect(0, 0, 150, 65));
		}
	}

	pixelPos = sf::Mouse::getPosition(menuWindow);
	worldPos = menuWindow.mapPixelToCoords(pixelPos);
	// Check if menu Play Button is clicked
	if (gameMode == menu && btnPlay->getSprite()->getGlobalBounds().contains(worldPos.x, worldPos.y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnPlay->getSprite()->setTextureRect(sf::IntRect(257, 0, 256, 75));
		if (event.type == sf::Event::MouseButtonReleased) {
			initGame();
			menuWindow.setVisible(false);
			btnPlay->getSprite()->setTextureRect(sf::IntRect(0, 0, 256, 75));
		}
	}

	// Check if menu Options Button is clicked
	if (gameMode == menu && btnOptions->getSprite()->getGlobalBounds().contains(worldPos.x, worldPos.y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnOptions->getSprite()->setTextureRect(sf::IntRect(449, 0, 448, 75));
		if (event.type == sf::Event::MouseButtonReleased) {
			btnOptions->getSprite()->setTextureRect(sf::IntRect(0, 0, 448, 75));
		}
	}

	// Check if menu Exit Button is clicked
	if (gameMode == menu && btnExit->getSprite()->getGlobalBounds().contains(worldPos.x, worldPos.y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnExit->getSprite()->setTextureRect(sf::IntRect(255, 0, 254, 75));
		if (event.type == sf::Event::MouseButtonReleased) {
			menuWindow.close();
			btnExit->getSprite()->setTextureRect(sf::IntRect(0, 0, 254, 75));
		}
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (scenePlaying) scenePlaying = false;
		//std::cout << "x: " << worldPos.x << " y: " << worldPos.y << std::endl;
	}

}

//
// Loads level from LevelManager
//
void GameEngine::loadLevel(LevelManager::Level level) {
	player.startPosition = Vector2(level.startPosition);
	player.stoppedLeft = false; player.stoppedRight = true;
	player.respawn();
	levelManager.setLevel(level);


	sf::String title("SuperNova - Level " + std::to_string(level.levelNumber));
	gameWindow.setTitle(title);
	setWindowView(gameWindow, tileSize * level.width, tileSize * level.height);
}

//
// Adding background sound to the game
// ** Using code from url: https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Music.php
//
void GameEngine::playMusic()
{
	// Open the Background Music
	if (!music.openFromFile("src/resources/sounds/background_sound.wav")) {
		std::cout << "Could not load background_music" << std::endl;
		return;
	}

	music.setVolume(10);

	music.setLoop(true);         // make it loop
	// Play it
	music.play();
}

//
// Set and center window
//
void GameEngine::setWindowView(sf::RenderWindow& window, float width, float height) {
	auto desktop = sf::VideoMode::getDesktopMode();
	viewWidth = width;
	viewHeight = height;

	if (window.getSize().x != desktop.width) { // if window is not full screen
		window.setSize(sf::Vector2u(viewWidth, viewHeight));
		window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));

		view.setSize(viewWidth, viewHeight + gamebar.getSize().y);
		view = getViewport(viewWidth, viewHeight);
		view.setCenter(view.getSize().x / 2, (view.getSize().y / 2));
	}
	else {
		view = getViewport(window.getSize().x, window.getSize().y);
		view.setSize(viewWidth, viewHeight);
		view.setCenter(view.getSize().x / 2, (view.getSize().y / 2));
	}
}

//
// Updates all game objects
//
void GameEngine::updateGame() {
	if (gameMode == scene) storyManager.update();

	player.update(levelManager.getCurrentLevel());

	Sprite::animateAll();

	sf::Vector2i pixelPos(player.getX(), player.getY());
	sf::Vector2f worldPos = gameWindow.mapPixelToCoords(pixelPos);
	pixiguide->getSprite()->setPosition(sf::Vector2f((pixelPos.x - (4.5 * 64)) * 1.1, (pixelPos.y - (2*64))/1.2));
	if (player.getBoundingBox().intersects(pixiguide->getBoundingBox())) {
		pixiguide->getSprite()->move(100,0);
	}
}

//
// Updates all menu objects
//
void GameEngine::updateMenu() {
	gameWindow.setVisible(false);
	blackRect.setSize(sf::Vector2f(menuWindow.getSize()));
}