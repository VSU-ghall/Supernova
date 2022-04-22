#include "headers/GameEngine.h"

GameEngine::GameEngine() 
	:gameWindow(sf::VideoMode(), "SuperNova"), menuWindow(sf::VideoMode(), "SuperNova - Menu"), storyManager(&gameWindow, &scenePlaying, &displayingText)
{}

void GameEngine::run() {
	initMenu();

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
				if (player.dead) {
					drawGame();
					break;
				}
				updateGame();
				drawGame();
				break;
		}
		
	}
}

void GameEngine::initGame() {
	gameWindow.setFramerateLimit(60);

	if (gameMode != paused) {

		player.init(&displayingText);
		loadLevel(levelManager.getLevel1(), levelManager.getLevel1().leftStartPosition);


		gameBar.setFillColor(sf::Color(59, 30, 11));
		chatBar.setFillColor(sf::Color(0,0,0,200));
		btnMenu->getSprite()->setTextureRect(sf::IntRect(0, 0, 150, 65));


		hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
		hpBarInside.setFillColor(sf::Color::Green);

		hpBarBack.setSize(sf::Vector2f(HP_BAR_WIDTH, HP_BAR_HEIGHT));
		hpBarInside.setSize(sf::Vector2f(HP_BAR_WIDTH * player.getHp(), HP_BAR_HEIGHT));

		if (!gameOverText.loadFromFile("src/resources/Game_Over_Screen.png"))
			std::cout << "couldn't load game over display" << std::endl;

		gameOver.setTexture(&gameOverText);
		gameOverBackground.setFillColor(sf::Color(255, 0, 0, 100));

		//storyManager.playLogoIntro();
		//storyManager.playTextIntro();
		addEntities();
	}
	else {
		sf::Vector2u winSize = gameWindow.getSize();
		setWindowView(gameWindow, static_cast<float>( tileSize * levelManager.currentLevel.width), static_cast<float>(tileSize * levelManager.currentLevel.height));
		gameWindow.setSize(winSize);
	}

	gameMode = game;
	gameWindow.setVisible(true); menuWindow.setVisible(false);

	playMusic();
}

void GameEngine::initMenu() {
	menuWindow.setFramerateLimit(60);
	setWindowView(menuWindow, static_cast<float>(tileSize * 20), static_cast<float>(tileSize * 20));

	if (gameMode != paused) {
		blackRect.setFillColor(sf::Color(0, 10, 0, 255));
		blackRect.setSize(sf::Vector2f(menuWindow.getSize()));

		// All menu buttons are centered and linked together, so if you vertically move the first, the others with it.
		btnPlay->getSprite()->setTextureRect(sf::IntRect(0, 0, 256, 75));
		btnPlay->getSprite()->setPosition((menuWindow.getSize().x - static_cast<float>(256)) / 2, (menuWindow.getSize().y - static_cast<float>(74 * 5)) / 2);

		btnOptions->getSprite()->setTextureRect(sf::IntRect(0, 0, 448, 75));
		btnOptions->getSprite()->setPosition((menuWindow.getSize().x - static_cast<float>(448)) / 2, btnPlay->getSprite()->getPosition().y + (74 * 2));

		btnExit->getSprite()->setTextureRect(sf::IntRect(0, 0, 254, 75));
		btnExit->getSprite()->setPosition((menuWindow.getSize().x - static_cast<float>(254)) / 2, btnOptions->getSprite()->getPosition().y + (74 * 2));

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
		for (auto &e : enemies.getEntities()) {
			if (e->getTag() == levelManager.getCurrentLevel()->levelName) {
				gameWindow.draw(*e->getSprite()->getSprite());
			}
			
		}

		if (!levelManager.currentLevel.objects.empty())
			for (auto obj : levelManager.currentLevel.objects) {

				gameWindow.draw(*obj->getObject()->getSprite());
				if (obj->hasIcon()) gameWindow.draw(*obj->getIcon()->getSprite());
			}
	}
	
	if (scenePlaying || displayingText) storyManager.draw();

	if (player.dead) {
		gameWindow.draw(gameOverBackground);
		gameWindow.draw(gameOver);
	}

	gameWindow.display();
}

//
// Draws grid for development/testing purposes
//
void GameEngine::drawGrid() {
	for (unsigned int x = 0; x <= gameWindow.getSize().x; x = x + tileSize) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(static_cast<float>(x), 0);
		lines[0].color = sf::Color::White;
		lines[1].position = sf::Vector2f(static_cast<float>(x), static_cast<float>(gameWindow.getSize().y));
		lines[1].color = sf::Color::White;

		gameWindow.draw(lines);
	}

	for (unsigned int y = 0; y <= gameWindow.getSize().y; y = y + tileSize) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(0, static_cast<float>(y));
		lines[0].color = sf::Color::White;
		lines[1].position = sf::Vector2f(static_cast<float>(gameWindow.getSize().x), static_cast<float>(y));
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
		view = getViewport(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
		if (gameMode == game) updateComponentView();
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
		loadLevel(levelManager.getLevel2(), levelManager.getLevel2().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		loadLevel(levelManager.getLevel3(), levelManager.getLevel3().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		loadLevel(levelManager.getLevel4(), levelManager.getLevel4().topStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		loadLevel(levelManager.getLevel5(), levelManager.getLevel5().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		loadLevel(levelManager.getLevel6(), levelManager.getLevel6().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		loadLevel(levelManager.getLevel7(), levelManager.getLevel7().topStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		loadLevel(levelManager.getLevel8(), levelManager.getLevel8().topStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
		loadLevel(levelManager.getLevel9(), levelManager.getLevel9().leftStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		loadLevel(levelManager.getLevel10(), levelManager.getLevel10().rightStartPosition);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen))
		loadLevel(levelManager.getLevel11(), levelManager.getLevel11().leftStartPosition);

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
				// Drill
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
				//boots
				if (obj->getIconIndex() == 2) {
					if (player.dashBoots) {
						player.dashBoots = false;
						obj->getIcon()->getSprite()->setColor(sf::Color(100, 100, 100, 255));
					}
					else {
						player.dashBoots = true;
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
	setWindowView(gameWindow, static_cast<float>(tileSize * level.width), static_cast<float>(tileSize * level.height));

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
		view = getViewport(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
		view.setSize(viewWidth, viewHeight);
		view.setCenter(view.getSize().x / 2, (view.getSize().y / 2));

		updateComponentView();
	}
}

//
// Updates all game objects
//
void GameEngine::updateGame() {
	if (player.playingDeath) {
		player.update(levelManager.getCurrentLevel());
		return;
	}

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
			// static enemies
			if (!e->isDynamic() && !e->getSprite()->animating && checkCollision(*e->getSprite()->getSprite(), player.getSprite())) {
				e->getSprite()->animateOnce();
				player.takeDamage(e->getDamageDealt());
				e->notInteractable();
				//std::cout << player.getHp() << " hp\n";
			}

			// dynamic enemies
			if (e->isDynamic() && checkCollision(*e->getSprite()->getSprite(), player.getSprite())) {
				if (e->getSprite()->hasSpecial() && !e->getSprite()->animatingSpecial && !e->isInCooldown()) {
					e->attack();
					player.takeDamage(e->getDamageDealt());
				}
				else if (!e->isInCooldown()) {
					e->attack();
					player.takeDamage(e->getDamageDealt());
				}
			}

			if (!levelManager.currentLevel.objects.empty()) {
				for (auto obj : levelManager.currentLevel.objects)
					if (obj->isBullet())
						if (checkCollision(*e->getSprite()->getSprite(), *obj->getObject()->getSprite())) {
							levelManager.removeObject(&levelManager.currentLevel, obj);
							e->takeDamage();;
						}
			}
		}
	}

	if (hpBarInside.getSize().y != HP_BAR_WIDTH * player.getHp()) updateHpBar();
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

void GameEngine::initJetPackBar() {
	jetPackInside.setSize(sf::Vector2f(FUEL_BAR_WIDTH, FUEL_BAR_HEIGHT * player.getJetPackFuel() / player.JETPACK_MAXIMUM));
	jetPackBack.setSize(sf::Vector2f(FUEL_BAR_WIDTH, FUEL_BAR_HEIGHT));
	jetPackBack.setFillColor(sf::Color(50, 50, 50, 200));
	jetPackBack.setPosition(10, 100);

	jetPackInside.setSize(sf::Vector2f(FUEL_BAR_WIDTH, FUEL_BAR_HEIGHT * (player.getJetPackFuel() / player.JETPACK_MAXIMUM)));
	jetPackInside.setFillColor(sf::Color(173, 255, 230, 200));
	jetPackInside.setPosition(10, 100);
}

void GameEngine::updateComponentView() {
	// Set the game bar and contents
	gameBar.setSize(sf::Vector2f(view.getSize().x, 75));

	// Populate all the item icons
	for (auto obj : levelManager.icons)
		obj->getIcon()->getSprite()->setPosition(gameBar.getPosition().x + (10 * (obj->getIconIndex() + 1)) + (obj->getSize().x * obj->getIconIndex()),
			gameBar.getPosition().y + ((gameBar.getSize().y - obj->getSize().y) / 2));

	btnMenu->getSprite()->setPosition(gameBar.getSize().x -
		(btnMenu->getTexture().getSize().x / static_cast<float>(2)) - 10, gameBar.getPosition().y + 5);

	float xPos = gameBar.getSize().x / 2 - 150;
	float yPos = gameBar.getSize().y / 5;


	hpBarBack.setPosition(xPos, yPos);
	hpBarInside.setPosition(xPos, yPos);

	// Set the text bar
	chatBar.setSize(sf::Vector2f(view.getSize().x, 100));
	chatBar.setPosition(0, view.getSize().y - chatBar.getSize().y);

	gameOverBackground.setSize(sf::Vector2f(view.getSize().x, view.getSize().y - gameBar.getSize().y));
	gameOverBackground.setPosition(0, gameBar.getSize().y);

	float scale = (view.getSize().x / 2) / gameOverText.getSize().x;
	gameOver.setSize(sf::Vector2f(gameOverText.getSize().x * scale, gameOverText.getSize().y * scale));
	gameOver.setPosition(sf::Vector2f(view.getSize().x / 2 - gameOver.getSize().x / 2, view.getSize().y / 2 - gameOver.getSize().y / 2));
}

void GameEngine::updateHpBar() {
	hpBarInside.setSize(sf::Vector2f(HP_BAR_WIDTH * player.getHp(), HP_BAR_HEIGHT));
	sf::Color color = hpBarInside.getFillColor();

	color.r = static_cast <unsigned int>(255 * (1 - player.getHp()));
	color.g = static_cast <unsigned int>(255 * player.getHp());

	hpBarInside.setFillColor(color);
}

void GameEngine::updateJetPackBar() {
	jetPackInside.setSize(sf::Vector2f(FUEL_BAR_WIDTH, FUEL_BAR_HEIGHT * player.getJetPackFuel()/player.JETPACK_MAXIMUM));
}

bool GameEngine::checkCollision(const sf::Sprite & a, const sf::Sprite & b) {
	sf::Image imgA = a.getTexture()->copyToImage();
	sf::Image imgB = b.getTexture()->copyToImage();
	sf::FloatRect intersection;

	if (a.getGlobalBounds().intersects(b.getGlobalBounds(), intersection)) {
		const sf::Transform& inverseA(a.getInverseTransform());
		const sf::Transform& inverseB(b.getInverseTransform());

		const sf::Vector2u& sizeA(imgA.getSize());
		const sf::Vector2u& sizeB(imgB.getSize());

		const sf::Uint8* pixA = imgA.getPixelsPtr();
		const sf::Uint8* pixB = imgB.getPixelsPtr();

		sf::Vector2f vecA, vecB;
		int xMax = intersection.left + intersection.width;
		int yMax = intersection.top + intersection.height;

		for (int x = intersection.left; x < xMax; x++)
			for (int y = intersection.top; y < yMax; y++) {
				vecA = inverseA.transformPoint(x, y);
				vecB = inverseB.transformPoint(x, y);

				int idxA = ((int)vecA.x + ((int)vecA.y) * sizeA.x) * 4 + 3;
				int idxB = ((int)vecB.x + ((int)vecB.y) * sizeB.x) * 4 + 3;

				if (vecA.x > 0 && vecA.y > 0 &&
					vecB.x > 0 && vecB.y > 0 &&
					vecA.x < sizeA.x && vecA.y < sizeA.y &&
					vecB.x < sizeB.x && vecB.y < sizeB.y &&
					pixA[idxA] > 0 &&
					pixB[idxB] > 0) {
					return true;
				}
			}
	}

	return false;
}