#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>

extern class Sprite
{
	public:
		sf::Sprite sprite;
		sf::Texture texture;
		bool animating = false, animatingSpecial = false;

		Sprite();
		Sprite(const std::string& filePath);
		Sprite(const std::string& filePath, bool animated, bool random, int numFrames, int width, int height, float scale, int frequency);

		void animate();
		static void animateAll();
		void animateOnce();
		void animateSpecial();
		void flip();

		std::string& getFilePath();
		int getFrequency();
		int getHeight();
		int getNumFrames();
		float getScale();
		sf::Sprite* getSprite();
		sf::Texture getTexture();
		sf::Clock getTimer();
		int getWidth();
		sf::FloatRect getBoundingBox();

		bool hasSpecial();
		bool isAnimated();
		bool isRandom();

		void setBounds(int width, int height);
		void setSpecial(int numFrames, int left, int top, int width, int height);
		
	private:
		std::string filePath;
		int left = 0, top = 0, width, height, frequency, numFrames, offset = 0,
			boundWidth = 0, boundHeight = 0,
			specialLeft, specialTop, specialNumFrames, specialWidth, specialHeight;
		float scale;
		bool animated = false, random = false, special = false;
		sf::Clock timer;
};
static std::vector<Sprite*> sprites;