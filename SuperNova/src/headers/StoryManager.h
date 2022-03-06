#pragma once
#include "iostream"
#include <SFML/Graphics.hpp>
#include "headers/Sprite.h"

extern class StoryManager
{
public:
	StoryManager(sf::RenderWindow* window, bool* scenePlaying) {
		this->window = window;
		this->scenePlaying = scenePlaying;

		blackRect.setFillColor(sf::Color(0, 0, 0, 255));
	}

	void draw();
	void update();

	/*** Scene Methods ***/
	void playLogoIntro();
	void playIntroScene();

private:
	sf::RenderWindow* window;
	sf::Clock timer;
	bool* scenePlaying;

	/*** Sprites and Textures ***/
	sf::RectangleShape blackRect, logoImg;
	Sprite* rocket, *astronaut, *planetSurfaceBackground = new Sprite("src/resources/planet_surface.png", false, false, 1, 200, 120, 7.0, 0);
	sf::Texture logoImgText;

	/*** Booleans ***/
	bool playingLogo = false, 
		playingIntro = false, introFadedOut = false;


	/*** Helper Methods ***/
	void fadeIn(sf::RectangleShape& rect, int speed);
	void fadeOut(sf::RectangleShape& rect, int speed);
};

