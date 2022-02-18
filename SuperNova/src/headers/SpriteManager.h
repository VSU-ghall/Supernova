#pragma once
#include "Vector2.h"
#include "iostream"
#include <SFML/Graphics.hpp>

static class SpriteManager {
	public: 
		struct Object {
			SpriteManager* spriteManager;
			sf::Sprite sprite;
			sf::Texture texture;
			sf::Clock timer;
			bool isAnimated = false, animating = false;
			int id = spriteManager->numObjects++, width, height, frequency, numFrames;
		};

		void animate();
		Object loadSprite(const std::string& filename);
		void loadSprite(const std::string& filename, bool isAnimated, int numFrames, int width, int height, int frequency);

	private:
		int numObjects = 0;
		Object *objects;
};
