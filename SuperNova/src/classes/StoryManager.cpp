#include "headers/StoryManager.h"

void StoryManager::draw() {
	float seconds = timer.getElapsedTime().asSeconds();

	if (playingLogo) {
		if (seconds <= 7) window->draw(blackRect);
		window->draw(logoImg);
	}
	if (playingIntro) {
		window->draw(*astronaut->getSprite());
		window->draw(*rocket->getSprite());
	}
}

void StoryManager::update() {
	float seconds = timer.getElapsedTime().asSeconds();

	if (playingLogo) {
		if (seconds >= 7 && logoImg.getFillColor().a >= 3) fadeOut(logoImg);
		else if (seconds >= 2 && logoImg.getFillColor().a < 254) fadeIn(logoImg);

		if (seconds >= 7 && logoImg.getFillColor().a <= 0) {
			*scenePlaying = false;
			playingLogo = false;
		}
	}
	if (playingIntro) {
		sf::Vector2f rocketPos = rocket->getSprite()->getPosition();
		rocketPos.y += 3 + -rocketPos.y/(3*64);

		if (rocketPos.y <= 6 * 64) {
			rocket->getSprite()->setPosition(rocketPos);
			astronaut->getSprite()->setPosition(64, rocket->getSprite()->getPosition().y - 100);
		}
		else {
			//*scenePlaying = false;
			//playingIntro = false;
		}
	}
}

/********************************* Scenes *********************************/

void StoryManager::playLogoIntro() {
	*scenePlaying = true; playingLogo = true;
	timer.restart();

	if (!logoImgText.loadFromFile("src/resources/logo_screen.png")) {
		std::cout << "there was a problem loading the logo screen" << std::endl;
		return;
	}
	logoImg.setTexture(&logoImgText);

	sf::Color color = logoImg.getFillColor();
	color.a = 0;
	logoImg.setFillColor(color);

	logoImg.setSize(sf::Vector2f(window->getSize()));
	blackRect.setSize(sf::Vector2f(window->getSize()));
}

void StoryManager::playIntroScene() {
	*scenePlaying = true; playingIntro = true;
	timer.restart();

	//const std::string& filePath, bool animated, bool random, int numFrames, 
	//		int width, int height, float scale, int frequency
	rocket = new Sprite("src/resources/rocket_sprite_sheet.png", true, false, 3, 1024, 1535, 0.25, 100);
	astronaut = new Sprite("src/resources/astronaut_walk.png", false, false, 8, 800, 1668, 1.0f, 100);

	//800, 1668

	rocket->getSprite()->setPosition(64,-1535*0.125+50);
}

/**************************************************************************/
/***************************** Helper Methods *****************************/
/**************************************************************************/

void StoryManager::fadeIn(sf::RectangleShape& rect) {
	sf::Color color = rect.getFillColor();
	color.a += 2;

	rect.setFillColor(color);
}

void StoryManager::fadeOut(sf::RectangleShape& rect) {
	sf::Color color = rect.getFillColor();
	color.a -= 3;

	rect.setFillColor(color);
}