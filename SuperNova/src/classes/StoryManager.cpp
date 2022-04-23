#include "headers/StoryManager.h"

void StoryManager::draw() {
	float seconds = timer.getElapsedTime().asSeconds();

	if (playingLogo) {
		if (seconds <= 7) window->draw(blackRect);
		else window->draw(*planetSurfaceBackground->getSprite());
		window->draw(logoImg);
	}
	if (playingIntro) {

		if (introFadedOut) {
			window->draw(blackRect);
			return;
		}

		window->draw(*planetSurfaceBackground->getSprite());

		if (rocket->getSprite()->getPosition().y >= 3 * 64)
			window->draw(*astronaut->getSprite());
		if (seconds >= 2) window->draw(*rocket->getSprite());

		window->draw(blackRect);
	}
	if (playingWalkOut) {
		if (seconds >= 0.2)
			window->draw(*astronaut->getSprite());
	}
	if (playingTextIntro) {
		window->draw(displayText);
		window->draw(*pixiIcon->getSprite());
	}
}

void StoryManager::update() {
	float seconds = timer.getElapsedTime().asSeconds();
	if (displayText.getPosition().y == 0) displayText.setPosition(10, window->getSize().y - 100 + 10);

	if (playingLogo) {
		if (seconds >= 7 && logoImg.getFillColor().a >= 3) fadeOut(logoImg, 3);
		else if (seconds >= 2 && logoImg.getFillColor().a < 254) fadeIn(logoImg, 2);

		if (seconds >= 7 && logoImg.getFillColor().a <= 0) {
			//*scenePlaying = false;
			playingLogo = false;
			playIntroScene();
		}
	}
	if (playingIntro) {
		if (seconds <= 2) return;

		sf::Vector2f rocketPos = rocket->getSprite()->getPosition();
		rocketPos.y += 3 + -rocketPos.y/(3*64);

		if (rocketPos.y <= 5 * 64) {
			rocket->getSprite()->setPosition(rocketPos);
			astronaut->getSprite()->setPosition(192, (rocket->getSprite()->getPosition().y + (96 * 4.0)) - 220);
		}
		else {
			if (rocket->animating) {
				rocket->animating = false;
				rocket->getSprite()->setTextureRect(sf::IntRect(64*3, 0, 64, 96));
			}

			sf::Vector2f astronautPos = astronaut->getSprite()->getPosition();

			if (astronautPos.y <= rocket->getSprite()->getPosition().y + (96 * 4.0) - 128)
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

						if (seconds >= 12.5f && seconds <= 16 && blackRect.getFillColor().a < 254) fadeIn(blackRect, 2);
						else {
							if (seconds < 12.5f) return;
							if (!introFadedOut) introFadedOut = true;
							
							if (blackRect.getFillColor().a >= 3) fadeOut(blackRect, 1.5f);
							else {
								//*scenePlaying = false;
								playingIntro = false;
								playWalkOut();
							}
						}
					}
				}
			}
		}
	}
	if (playingWalkOut) {
		sf::Vector2f astronautPos = astronaut->getSprite()->getPosition();
		astronaut->getSprite()->setPosition(astronautPos.x + 2.5, astronautPos.y);

		if (astronautPos.x >= 2*64) {
			playTextIntro();
			*scenePlaying = false;
			playingWalkOut = false;
		}
	}
	if (playingTextIntro) {
		sf::String text;
		if (seconds >= 55) {
			playingTextIntro = false; *displayingText = false;
		}
		else if (seconds >= 45) {
			text = "Use the A & D keys to move right & left, the S key to crouch, and the W key to \njump!";
		}
		else if (seconds >= 35) {
			text = "Maybe we'll even find some cool weapons or gadgets to use along the way!";
		}
		else if (seconds >= 30) {
			text = "Well, only one way to go anyway! I'm sure seeing will jog my memory.";
		}
		else if (seconds >= 25) {
			text = ". . .";
		}
		else if (seconds >= 24.5) {
			text = ". .";
		}
		else if (seconds >= 24) {
			text = ".";
		}
		else if (seconds >= 20) {
			text = "It's been so long I don't quite remember";
		}
		else if (seconds >= 15) {
			text = "What's this? You wanna know how to get out of here?";
		}
		else if (seconds >= 5) {
			text = "You're the first soul I've seen in many years! These caverns have been abandoned";
			text += "\nsince my creators mysteriously disappeared.";
		}
		else if (seconds >= 0) {
			text = "Welcome traveler!";
		}

		displayText.setString(text);
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

	sf::Color color = blackRect.getFillColor();
	color.a = 0;
	blackRect.setFillColor(color);

	rocket->getSprite()->setPosition(64, -96*4.0 +50);
}

void StoryManager::playWalkOut() {
	*scenePlaying = true; playingWalkOut = true;
	timer.restart();

	astronaut = new Sprite("src/resources/astronaut_walk.png", true, false, 8, 32, 64, 2.f, 150);

	astronaut->getSprite()->setPosition(-64, 7*64);
}

void StoryManager::playTextIntro() {
	*displayingText = true; playingTextIntro = true;
	timer.restart();

	sf::Vector2i pixiSize(pixiIcon->getWidth() * pixiIcon->getScale(), pixiIcon->getHeight() * pixiIcon->getScale());

	pixiIcon->getSprite()->setPosition(0, window->getSize().y - pixiSize.y + 25);
	if (displayText.getPosition().y == 0) displayText.setPosition(pixiSize.x, window->getSize().y - 100 + 5);
}

/**************************************************************************/
/***************************** Helper Methods *****************************/
/**************************************************************************/

void StoryManager::fadeIn(sf::RectangleShape& rect, int speed) {
	sf::Color color = rect.getFillColor();
	color.a += speed;

	rect.setFillColor(color);
}

void StoryManager::fadeOut(sf::RectangleShape& rect, int speed) {
	sf::Color color = rect.getFillColor();
	color.a -= speed;

	rect.setFillColor(color);
}