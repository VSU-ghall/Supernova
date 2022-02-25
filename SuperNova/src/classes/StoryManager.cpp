#include "headers/StoryManager.h"

void StoryManager::draw() {
	if (playingIntro) {

		if (timer.getElapsedTime().asSeconds() <= 7) window->draw(blackRect);
		window->draw(logoImg);
	}
}

void StoryManager::playIntroduction() {
	*scenePlaying = true; playingIntro = true;
	timer.restart();

	sf::Color color = logoImg.getFillColor();
	color.a = 0;
	logoImg.setFillColor(color);

	logoImg.setSize(sf::Vector2f(window->getSize()));
	blackRect.setSize(sf::Vector2f(window->getSize()));
}

void StoryManager::update() {
	float seconds = timer.getElapsedTime().asSeconds();
	if (playingIntro) {
		if (seconds >= 7 && logoImg.getFillColor().a >= 3) fadeOut(logoImg);
		else if (seconds >= 2 && logoImg.getFillColor().a < 254) fadeIn(logoImg);

		if (seconds >= 7 && logoImg.getFillColor().a <= 0) {
			*scenePlaying = false;
			playingIntro = false;
		}
	}
}

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