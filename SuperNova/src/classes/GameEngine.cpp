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

		player.init(&displayingText);
		loadLevel(levelManager.getLevel1(), levelManager.getLevel1().leftStartPosition);


		gameBar.setFillColor(sf::Color(59, 30, 11));
		chatBar.setFillColor(sf::Color(0,0,0,200));
		btnMenu->getSprite()->setTextureRect(sf::IntRect(0, 0, 150, 65));

		//storyManager.playLogoIntro();
		storyManager.playTextIntro();
		addEntities();
	}
	else {
		sf::Vector2u winSize = gameWindow.getSize();
		setWindowView(gameWindow, tileSize * levelManager.currentLevel.width, tileSize * levelManager.currentLevel.height);
		gameWindow.setSize(winSize);
	}

	gameMode = game;
	gameWindow.setVisible(true); menuWindow.setVisible(false);

	playMusic();
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
	for (auto obj : levelManager.icons) gameWindow.draw(*obj->getIcon()->getSprite());
	gameWindow.draw(*btnMenu->getSprite());
	gameWindow.draw(hpBarBack);
	gameWindow.draw(hpBarInside);

	if (player.jetPack) {
		gameWindow.draw(jetPackBack);
		gameWindow.draw(jetPackInside);
	}
	if (displayingText) gameWindow.draw(chatBar);

	if (!scenePlaying) {
		for (auto e : enemies.getEntities()) {
			if (e->getTag() == levelManager.getCurrentLevel().levelName) {
				gameWindow.draw(*e->getSprite()->getSprite());
				e->getSprite()->getSprite()->setPosition(e->getPosition());
			}
			
		}

		if (!levelManager.currentLevel.objects.empty())
			for (auto obj : levelManager.currentLevel.objects) {

				gameWindow.draw(*obj->getObject()->getSprite());
				if (obj->hasIcon()) gameWindow.draw(*obj->getIcon()->getSprite());
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

			// Populate all the item icons
			for (auto obj : levelManager.icons)
				obj->getIcon()->getSprite()->setPosition(gameBar.getPosition().x + (10 * (obj->getIndex()+1) ) + (obj->getSize().x * obj->getIndex()),
					gameBar.getPosition().y + ((gameBar.getSize().y - obj->getSize().y) / 2));

			btnMenu->getSprite()->setPosition(gameBar.getSize().x - 
								(btnMenu->getTexture().getSize().x/2) - 10, gameBar.getPosition().y + 5);

			float width = 300.f;
			float height = 50.f;
			float xPos = gameBar.getSize().x /2 - 150;
			float yPos = gameBar.getSize().y / 5;
			

			hpBarBack.setSize(sf::Vector2f(width, height));
			hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
			hpBarBack.setPosition(xPos, yPos);

			hpBarInside.setSize(sf::Vector2f(width * player.getHp(), height));
			hpBarInside.setFillColor(sf::Color(250, 0, 0, 200));
			hpBarInside.setPosition(xPos, yPos);
			
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
		loadLevel(levelManager.getLevel1(),levelManager.getLevel1().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		loadLevel(levelManager.getLevel2(), levelManager.getLevel1().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		loadLevel(levelManager.getLevel3(), levelManager.getLevel1().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		loadLevel(levelManager.getLevel4(), levelManager.getLevel1().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		loadLevel(levelManager.getLevel5(), levelManager.getLevel1().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		loadLevel(levelManager.getLevel6(), levelManager.getLevel1().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		loadLevel(levelManager.getLevel7(), levelManager.getLevel1().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		loadLevel(levelManager.getLevel8(), levelManager.getLevel1().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
		loadLevel(levelManager.getLevel9(), levelManager.getLevel1().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		loadLevel(levelManager.getLevel10(), levelManager.getLevel1().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen))
		loadLevel(levelManager.getLevel11(), levelManager.getLevel1().leftStartPosition);

	sf::Vector2i pixelPos = sf::Mouse::getPosition(gameWindow);
	sf::Vector2f worldPos = gameWindow.mapPixelToCoords(pixelPos);

	// Check if icons are clicked
	if (gameMode == game && event.type == sf::Event::MouseButtonReleased)
		for (auto obj : levelManager.icons) {
			if (obj->getIcon()->getSprite()->getGlobalBounds().contains(worldPos.x, worldPos.y) && !obj->hasHiddenIcon()) {
				// Jetpack
				if (obj->getIconIndex() == 0) {
					if (player.jetPack) {
						player.jetPack = false;
						obj->getIcon()->getSprite()->setColor(sf::Color(100, 100, 100, 255));
					}
					else {
						player.jetPack = true;
						obj->getIcon()->getSprite()->setColor(sf::Color(255, 255, 255, 255));
					}
				}
				//drill
				if (obj->getIconIndex() == 1) {
					if (player.drilling) {
						player.drilling = false;
						obj->getIcon()->getSprite()->setColor(sf::Color(100, 100, 100, 255));
					}
					else {
						player.drilling = true;
						obj->getIcon()->getSprite()->setColor(sf::Color(255, 255, 255, 255));
					}
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
void GameEngine::loadLevel(LevelManager::Level level, Vector2 startp) {
	player.startPosition = startp;
	player.stoppedLeft = false; player.stoppedRight = true;
	player.respawn();
	levelManager.setLevel(level);


	sf::String title("SuperNova - Level " + std::to_string(level.levelNumber));
	gameWindow.setTitle(title);
	setWindowView(gameWindow, tileSize * level.width, tileSize * level.height);

	sf::Vector2f pixiPos(player.getX() + 16, player.getY());

	pixiguide->getSprite()->setPosition(sf::Vector2f(pixiPos.x - 64, pixiPos.y - 64));

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
	Sprite::animateAll();

	if (scenePlaying) {
		storyManager.update();
		return;
	}

	if (displayingText) storyManager.update();

	if (player.transitioningLeft) {
		loadLevel(*levelManager.currentLevel.left, levelManager.currentLevel.left->rightStartPosition);
		player.transitioningLeft = false;
	}
	else if (player.transitioningRight) {
		loadLevel(*levelManager.currentLevel.right, levelManager.currentLevel.right->leftStartPosition);
		player.transitioningRight = false;
	}
	else if (player.transitioningTop) {
		loadLevel(*levelManager.currentLevel.top, levelManager.currentLevel.top->botStartPosition);
		player.transitioningTop = false;
	}
	else if (player.transitioningBot) {
		loadLevel(*levelManager.currentLevel.bot, levelManager.currentLevel.bot->topStartPosition);
		player.transitioningBot = false;
	}

	player.update(levelManager.getCurrentLevel());
	if (player.jetPack) {
		initJetPackBar();
		updateJetPackBar();
	}
	enemies.update();
	if (!enemies.getInteractableEntities(levelManager.currentLevel.levelName).empty()) {
		for (auto& e : enemies.getInteractableEntities(levelManager.currentLevel.levelName)) {
			if (player.getBoundingBox().intersects(e->getSprite()->getBoundingBox()) && !e->getSprite()->animating) {
				e->getSprite()->animateOnce();
				player.takeDamage(calculateDamage(*e));
				e->notInteractable();
				updateHpBar();
				//std::cout << player.getHp() << " hp\n";
			}
		}
	}

			levelManager.setLevel(levelManager.currentLevel);

}

//
// Updates all menu objects
//
void GameEngine::updateMenu() {
	//blackRect.setSize(sf::Vector2f(menuWindow.getSize()));
}

void GameEngine::addEntities() {
	for (auto& level : levelManager.getAllLevels()) {
		for (auto& e : level.enemies) {
			enemies.addEntity(e);
		}
	}
	
}

void GameEngine::updateJetPackBar() {
	jetPackInside.setSize(sf::Vector2f(50 , 300* player.getJetPackFuel()/player.JETPACK_MAXIMUM));
}
void GameEngine::initJetPackBar() {
	jetPackInside.setSize(sf::Vector2f(50, 300 * player.getJetPackFuel() / player.JETPACK_MAXIMUM));
	jetPackBack.setSize(sf::Vector2f(50, 300));
	jetPackBack.setFillColor(sf::Color(50, 50, 50, 200));
	jetPackBack.setPosition(10, 100 );

	jetPackInside.setSize(sf::Vector2f(50, 300 * (player.getJetPackFuel() / player.JETPACK_MAXIMUM)));
	jetPackInside.setFillColor(sf::Color(173, 255, 230, 200));
	jetPackInside.setPosition(10, 100);
}
void GameEngine::updateHpBar() {
	hpBarInside.setSize(sf::Vector2f(300 * player.getHp(), 50));
}
float GameEngine::calculateDamage(Entity e) {
	float dist = std::sqrt(std::pow(e.getPosition().x - player.getX(), 2) + std::pow(e.getPosition().y - player.getY(), 2));
	float damage = dist / 500;
	//std::cout << damage << " damage" << "\n";
	return damage;
}