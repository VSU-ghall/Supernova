#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

extern class Sprite
{
	public:
		sf::Sprite sprite;
		sf::Texture texture;
		bool animating = false;

		Sprite();
		Sprite(const std::string& filePath);
		Sprite(const std::string& filePath, bool animated, bool random, int numFrames, int width, int height, int frequency);

		void animate();
		void animateAll();
		sf::Sprite getSprite();
		sf::Texture getTexture();
		sf::Clock getTimer();
		int getWidth();

	private:
		int width, height, frequency, numFrames, offset = 0;
		bool animated = false, random = false;
		sf::Clock timer;
};
static std::vector<Sprite*> sprites;