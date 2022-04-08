#pragma once
#include "iostream"
#include <SFML/Graphics.hpp>
#include "headers/Sprite.h"

extern class StoryManager
{
public:
	StoryManager(sf::RenderWindow* window, bool* scenePlaying, bool *displayingText) {
		this->window = window;
		this->scenePlaying = scenePlaying;
		this->displayingText = displayingText;

		blackRect.setFillColor(sf::Color(0, 0, 0, 255));
		if (!font.loadFromFile("src/resources/calibril.ttf"))
			std::cout << "Couldn't load text font." << std::endl;

		displayText.setFillColor(sf::Color::White);
		displayText.setFont(font);
		displayText.setCharacterSize(36);
	}

	void draw();
	void update();

	/*** Scene Methods ***/
	void playLogoIntro();
	void playIntroScene();
	void playWalkOut();

	void playTextIntro();

private:
	sf::RenderWindow* window;
	sf::Clock timer;
	bool* scenePlaying, *displayingText;

	/*** Sprites and Textures ***/
	sf::RectangleShape blackRect, logoImg;
	Sprite* rocket, *astronaut, *planetSurfaceBackground = 
		new Sprite("src/resources/planet_surface.png", false, false, 1, 200, 120, 7.0, 0);
	sf::Texture logoImgText;
	sf::Text displayText; sf::Font font;

	/*** Booleans ***/
	bool playingLogo = false,
		playingIntro = false, introFadedOut = false,
		playingWalkOut = false,
		playingTextIntro = false;


	/*** Helper Methods ***/
	void fadeIn(sf::RectangleShape& rect, int speed);
	void fadeOut(sf::RectangleShape& rect, int speed);
};

