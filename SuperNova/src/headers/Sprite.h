#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Sprite
{
	public:
		sf::Sprite sprite;
		sf::Texture texture;

		bool isAnimating();
		void isAnimating(bool boolean);
		bool isAnimated();
		sf::Sprite getSprite();
		sf::Texture getTexture();
		sf::Clock getTimer();
		int getWidth();

		Sprite();
		Sprite(const std::string& filePath);
		Sprite(const std::string& filePath, bool isAnimated, int numFrames, int width, int height, int frequency);

	private:
		int id, width, height, frequency, numFrames;
		sf::Clock timer;
		bool animated = false, animating = false;
};