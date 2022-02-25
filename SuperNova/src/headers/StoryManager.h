#pragma once
#include "iostream"
#include <SFML/Graphics.hpp>

extern class StoryManager
{
public:

	StoryManager(sf::RenderWindow* window, bool* scenePlaying) {
		this->window = window;
		this->scenePlaying = scenePlaying;
		if (!logoImgText.loadFromFile("src/resources/logo_screen.png")) {
			std::cout << "there was a problem loading the logo screen" << std::endl;
			return;
		}
		logoImg.setTexture(&logoImgText);

		blackRect.setFillColor(sf::Color(0, 0, 0, 255));
	}

	void draw();
	void playIntroduction();
	void update();

private:
	sf::RenderWindow* window;
	bool* scenePlaying;
	bool playingIntro = false;
	sf::Clock timer;
	sf::RectangleShape logoImg, blackRect;
	sf::Texture logoImgText;

	void fadeIn(sf::RectangleShape& rect);
	void fadeOut(sf::RectangleShape& rect);
};

