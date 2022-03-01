#include "headers/StoryManager.h"

void StoryManager::draw() {
	float seconds = timer.getElapsedTime().asSeconds();

	if (playingLogo) {
		if (seconds <= 7) window->draw(blackRect);
		window->draw(logoImg);
	}
	if (playingIntro) {
		if (rocket->getSprite()->getPosition().y >= 3 * 64)
			window->draw(*astronaut->getSprite());
		if (seconds >= 0.1)
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
			//playIntroScene();
		}
	}
	if (playingIntro) {
		sf::Vector2f rocketPos = rocket->getSprite()->getPosition();
		rocketPos.y += 3 + -rocketPos.y/(3*64);

		if (rocketPos.y <= 6 * 64) {
			rocket->getSprite()->setPosition(rocketPos);
			astronaut->getSprite()->setPosition(192, (rocket->getSprite()->getPosition().y + (96 * 4.0)) - 220);
		}
		else {
			if (rocket->animating) {
				rocket->animating = false;
				rocket->getSprite()->setTextureRect(sf::IntRect(64*3, 0, 64, 96));
			}

			sf::Vector2f astronautPos = astronaut->getSprite()->getPosition();

			if (astronautPos.y <= 6 * 64 + (96 * 4.0) - 128)
				astronaut->getSprite()->setPosition(astronautPos.x+1, astronautPos.y+1);
			else {
				if (astronautPos.x <= 500)
					astronaut->getSprite()->setPosition(astronautPos.x + 1, astronautPos.y);
				else {
					if (astronaut->animating) {
						astronaut->animating = false;
						astronaut->getSprite()->setTextureRect(sf::IntRect(0, 0, 32, 64));
					}
					else {
						*scenePlaying = false;
						playingIntro = false;
					}
				}
			}
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

	rocket = new Sprite("src/resources/rocket_v2.png", true, false, 3, 64, 96, 4.0, 100);
	astronaut = new Sprite("src/resources/astronaut_walk.png", true, false, 8, 32, 64, 1.7f, 150);

	rocket->getSprite()->setPosition(64, -96*4.0 +50);
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