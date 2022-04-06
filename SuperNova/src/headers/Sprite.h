#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>

extern class Sprite
{
	public:
		sf::Sprite sprite;
		sf::Texture texture;
		bool animating = false;

		Sprite();
		Sprite(const std::string& filePath);
		Sprite(const std::string& filePath, bool animated, bool random, int numFrames, int width, int height, float scale, int frequency, bool startAnimated);
		Sprite(const std::string& filePath, bool animated, bool random, int numFrames, int width, int height, float scale, int frequency);

		void animate();
		void animateOnce();
		static void animateAll();
		sf::Sprite* getSprite();
		sf::Texture getTexture();
		sf::Clock getTimer();
		int getWidth();
		sf::FloatRect getBoundingBox();
		void setBounds(int width, int height);
	private:
		int width, height, frequency, numFrames, offset = 0,
			boundWidth = 0, boundHeight = 0;
		float scale;
		bool animated = false, random = false;
		sf::Clock timer;
};
static std::vector<Sprite*> sprites;