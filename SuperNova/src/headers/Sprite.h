#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>

extern class Sprite
{
	public:
		sf::Sprite sprite;
		sf::Texture texture;
		bool animating = false, animatingSpecial = false, animatingDamaged = false;

		Sprite();
		Sprite(const std::string& filePath);
		Sprite(const std::string& filePath, bool animated, bool random, int numFrames, int width, int height, float scale, int frequency);

		void animate();
		static void animateAll();
		void animateDamaged();
		void animateOnce();
		void animateSpecial();
		void flipHorizontal();
		void flipVertical();

		std::string& getFilePath();
		int getFrequency();
		int getHeight();
		int getNumFrames();
		float getScale();
		sf::Vector2f getScaledSize();
		sf::Sprite* getSprite();
		sf::Texture getTexture();
		sf::Clock getTimer();
		int getWidth();
		sf::FloatRect getBoundingBox();
		sf::Image getImage();

		bool hasDamaged();
		bool hasSpecial();
		bool isAnimated();
		bool isRandom();

		static void remove(Sprite* spr);
		void setBounds(int width, int height);
		void setDamaged(int left, int top, int width, int height);
		void setScale(float scale);
		void setSpecial(int numFrames, int left, int top, int width, int height);
		
	private:
		std::string filePath;
		int left = 0, top = 0, width, height, frequency, numFrames, offset = 0,
			boundWidth = 0, boundHeight = 0,
			specialLeft, specialTop, specialNumFrames, specialWidth, specialHeight,
			damagedLeft, damagedTop, damagedWidth, damagedHeight;
		float scale;
		bool animated = false, random = false, special = false, damaged = false, flippedHorizontal = false, flippedVertical = false;;
		sf::Clock timer;
		sf::Image image;
};
static std::vector<Sprite*> sprites;