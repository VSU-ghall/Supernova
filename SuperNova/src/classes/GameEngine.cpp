#include "headers/GameEngine.h"

GameEngine::GameEngine() 
	:gameWindow(sf::VideoMode(), "SuperNova"), menuWindow(sf::VideoMode(), "SuperNova - Menu"), storyManager(&gameWindow, &scenePlaying, &displayingText)
{}

void GameEngine::run() {
	init();

	// main loop --> continues each frame while window is open
	while (gameWindow.isOpen() && menuWindow.isOpen()) {
		// event handling
		sf::Event event;
		if (gameMode == menu || gameMode == paused)
			while (menuWindow.pollEvent(event))
				handleEvent(event);
		else if (gameMode == game)
			while (gameWindow.pollEvent(event))
				handleEvent(event);

		switch (gameMode) {
			case menu:
				updateMenu();
				drawMenu();
				break;
			case paused:
				updateMenu();
				drawMenu();
				break;
			case game:
				updateGame();
				drawGame();
				break;
		}
		
	}
}

//
//	Initializes the game components
//
void GameEngine::init() {
	initMenu();
}

void GameEngine::initGame() {
	gameWindow.setFramerateLimit(60);

	if (gameMode != paused) {
		loadLevel(levelManager.getLevel1());
		player.init();

		gameBar.setFillColor(sf::Color(59, 30, 11));
		chatBar.setFillColor(sf::Color(0,0,0,200));
		btnMenu->getSprite()->setTextureRect(sf::IntRect(0, 0, 150, 65));

		jetpackIcon.setSize(sf::Vector2f(64, 64));
		jetpackIcon.setFillColor(sf::Color::Red);

		//storyManager.playLogoIntro();
		storyManager.playTextIntro();
	}
	else {
		sf::Vector2u winSize = gameWindow.getSize();
		setWindowView(gameWindow, tileSize * levelManager.currentLevel.width, tileSize * levelManager.currentLevel.height);
		gameWindow.setSize(winSize);
	}

	gameMode = game;
	gameWindow.setVisible(true); menuWindow.setVisible(false);

	playMusic();

	addEntities();
}

void GameEngine::initMenu() {
	menuWindow.setFramerateLimit(60);
	setWindowView(menuWindow, tileSize * 20, tileSize * 20);

	if (gameMode != paused) {
		blackRect.setFillColor(sf::Color(0, 10, 0, 255));
		blackRect.setSize(sf::Vector2f(menuWindow.getSize()));

		// All menu buttons are centered and linked together, so if you vertically move the first, the others with it.
		btnPlay->getSprite()->setTextureRect(sf::IntRect(0, 0, 256, 75));
		btnPlay->getSprite()->setPosition((menuWindow.getSize().x - 256) / 2, (menuWindow.getSize().y - 74 * 5) / 2);

		btnOptions->getSprite()->setTextureRect(sf::IntRect(0, 0, 448, 75));
		btnOptions->getSprite()->setPosition((menuWindow.getSize().x - 448) / 2, btnPlay->getSprite()->getPosition().y + (74 * 2));

		btnExit->getSprite()->setTextureRect(sf::IntRect(0, 0, 254, 75));
		btnExit->getSprite()->setPosition((menuWindow.getSize().x - 254) / 2, btnOptions->getSprite()->getPosition().y + (74 * 2));

		gameMode = menu;
		gameWindow.setVisible(false);
	}

	playMusic();
	
	menuWindow.setVisible(true);
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

	if (!scenePlaying) player.draw(gameWindow);
	gameWindow.draw(*pixiguide->getSprite());

	gameWindow.draw(gameBar);
	gameWindow.draw(jetpackIcon);
	gameWindow.draw(*btnMenu->getSprite());

	if (displayingText) gameWindow.draw(chatBar);

	enemies.update();
	if (!scenePlaying) {
		for (auto e : enemies.getEntities()) {
			if (e->getTag() == levelManager.getCurrentLevel().levelName) {
				gameWindow.draw(*e->getSprite()->getSprite());
				e->getSprite()->getSprite()->setPosition(e->getPosition());
			}
			
		}
	}
	
	if (scenePlaying || displayingText) storyManager.draw();

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
		if (gameMode == game) gameWindow.close();
		else if (gameMode == menu || gameMode == paused) menuWindow.close();

	// sets viewport when window is resized
	if (event.type == sf::Event::Resized) {
		view = getViewport(event.size.width, event.size.height);
		if (gameMode == game) {
			// Set the game bar and contents
			gameBar.setSize(sf::Vector2f(view.getSize().x, 75));
			jetpackIcon.setPosition(gameBar.getPosition().x + 10, 
				gameBar.getPosition().y + ((gameBar.getSize().y - jetpackIcon.getSize().y)/2));
			btnMenu->getSprite()->setPosition(gameBar.getSize().x - 
				(btnMenu->getTexture().getSize().x/2) - 10, gameBar.getPosition().y + 5);
			
			// Set the text bar
			chatBar.setSize(sf::Vector2f(view.getSize().x, 100));
			chatBar.setPosition(0, view.getSize().y-chatBar.getSize().y);
		}
	}

	if (event.type == sf::Event::KeyReleased) {
		if (sf::Keyboard::D || sf::Keyboard::A)
			if (player.stoppedLeft || player.stoppedRight)
				player.moving = false;
	}

	// Temporary key bindings for development
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		loadLevel(levelManager.getLevel1());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		loadLevel(levelManager.getLevel2());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		loadLevel(levelManager.getLevel3());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		loadLevel(levelManager.getLevel4());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		loadLevel(levelManager.getLevel5());

	sf::Vector2i pixelPos = sf::Mouse::getPosition(gameWindow);
	sf::Vector2f worldPos = gameWindow.mapPixelToCoords(pixelPos);

	// Check if Jetpack Icon is clicked
	if (gameMode == game && jetpackIcon.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnMenu->getSprite()->setTextureRect(sf::IntRect(149, 0, 150, 65));*/
		if (event.type == sf::Event::MouseButtonReleased) {
			if (player.jetPack) {
				player.jetPack = false;
				jetpackIcon.setFillColor(sf::Color::Red);
			}else {
				player.jetPack = true;
				jetpackIcon.setFillColor(sf::Color::Green);
			}
		}
	}

	// Check if game Menu Button is clicked
	if (gameMode == game && btnMenu->getSprite()->getGlobalBounds().contains(worldPos.x, worldPos.y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnMenu->getSprite()->setTextureRect(sf::IntRect(149, 0, 150, 65));
		if (event.type == sf::Event::MouseButtonReleased) {
			gameMode = paused;
			initMenu();
			btnMenu->getSprite()->setTextureRect(sf::IntRect(0, 0, 150, 65));
		}
	}

	pixelPos = sf::Mouse::getPosition(menuWindow);
	worldPos = menuWindow.mapPixelToCoords(pixelPos);
	// Check if menu Play Button is clicked
	if ((gameMode == menu || gameMode == paused) && btnPlay->getSprite()->getGlobalBounds().contains(worldPos.x, worldPos.y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnPlay->getSprite()->setTextureRect(sf::IntRect(257, 0, 256, 75));
		if (event.type == sf::Event::MouseButtonReleased) {
			playSoundEffect("src/resources/sounds/main_menu_click.wav");
			initGame();
			btnPlay->getSprite()->setTextureRect(sf::IntRect(0, 0, 256, 75));
		}
	}

	// Check if menu Options Button is clicked
	if ((gameMode == menu || gameMode == paused) && btnOptions->getSprite()->getGlobalBounds().contains(worldPos.x, worldPos.y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnOptions->getSprite()->setTextureRect(sf::IntRect(449, 0, 448, 75));
		if (event.type == sf::Event::MouseButtonReleased) {
			playSoundEffect("src/resources/sounds/main_menu_click.wav");
			btnOptions->getSprite()->setTextureRect(sf::IntRect(0, 0, 448, 75));
		}
	}

	// Check if menu Exit Button is clicked
	if ((gameMode == menu || gameMode == paused) && btnExit->getSprite()->getGlobalBounds().contains(worldPos.x, worldPos.y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnExit->getSprite()->setTextureRect(sf::IntRect(255, 0, 254, 75));
		if (event.type == sf::Event::MouseButtonReleased) {
			playSoundEffect("src/resources/sounds/main_menu_click.wav");
			menuWindow.close();
			btnExit->getSprite()->setTextureRect(sf::IntRect(0, 0, 254, 75));
		}
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (scenePlaying) scenePlaying = false;
		if (displayingText) displayingText = false;
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
	if (gameMode == menu || gameMode == paused) {
		if (!music.openFromFile("src/resources/sounds/main_menu_sound.wav")) {
			std::cout << "Could not load main_menu_sound" << std::endl;
			return;
		}
	}
	else
		if (!music.openFromFile("src/resources/sounds/background_sound.wav")) {
			std::cout << "Could not load background_music" << std::endl;
			return;
		}

	music.setVolume(10);

	music.setLoop(true);         // make it loop
	// Play it
	music.play();
}

void GameEngine::playSoundEffect(const std::string& filePath) {
	if (!soundEffect.openFromFile(filePath)) {
		std::cout << "Could not load " << filePath << std::endl;
		return;
	}

	soundEffect.setVolume(10);

	soundEffect.play();
}

//
// Set and center window
//
void GameEngine::setWindowView(sf::RenderWindow& window, float width, float height) {
	auto desktop = sf::VideoMode::getDesktopMode();
	viewWidth = width;
	viewHeight = height;

	if (window.getSize().x != desktop.width) { // if window is not full screen
		view.setSize(viewWidth, viewHeight + gameBar.getSize().y);
		view = getViewport(viewWidth, viewHeight);
		view.setCenter(view.getSize().x / 2, (view.getSize().y / 2));

		window.setSize(sf::Vector2u(view.getSize()));
		window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
	}
	else {
		view = getViewport(window.getSize().x, window.getSize().y);
		view.setSize(viewWidth, viewHeight);
		view.setCenter(view.getSize().x / 2, (view.getSize().y / 2));

		gameBar.setSize(sf::Vector2f(view.getSize().x, 75));
		btnMenu->getSprite()->setPosition(gameBar.getSize().x - 150 - 10, gameBar.getPosition().y + 5);
	}
}

//
// Updates all game objects
//
void GameEngine::updateGame() {
	if (scenePlaying || displayingText) {
		storyManager.update();
		return;
	}

	if (player.transitioningLeft) {
		std::cout << levelManager.getCurrentLevel().levelNumber << std::endl;
		loadLevel(*levelManager.currentLevel.left);
		player.transitioningLeft = false;
	}
	else if (player.transitioningRight) {
		loadLevel(*levelManager.currentLevel.right);
		player.transitioningRight = false;
	}
	else if (player.transitioningTop) {
		loadLevel(*levelManager.currentLevel.top);
		player.transitioningTop = false;
	}
	else if (player.transitioningBot) {
		loadLevel(*levelManager.currentLevel.bot);
		player.transitioningBot = false;
	}

	player.update(levelManager.getCurrentLevel());

	Sprite::animateAll();

	sf::Vector2i pixelPos(player.getX(), player.getY());
	sf::Vector2f worldPos = gameWindow.mapPixelToCoords(pixelPos);
	pixiguide->getSprite()->setPosition(sf::Vector2f((pixelPos.x - (4.5 * 64)) * 1.1, (pixelPos.y - (2*64))/1.2));
	/*if (player.getBoundingBox().intersects(pixiguide->getBoundingBox())) {
		pixiguide->getSprite()->move(100,0);
	}*/
	for (auto e : enemies.getEntitiesInteractable()) {
		if (player.getBoundingBox().intersects(e->getSprite()->getBoundingBox()) && !e->getSprite()->animating) {
			e->getSprite()->animateOnce();
			e->notInteractable();
		}
	}
}

//
// Updates all menu objects
//
void GameEngine::updateMenu() {
	//blackRect.setSize(sf::Vector2f(menuWindow.getSize()));
}

void GameEngine::addEntities() {
	for (auto e : levelManager.getCurrentLevel().enemies) {
		enemies.addEntity(e);
	}
}