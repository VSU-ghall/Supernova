#include "headers/Sprite.h"

Sprite::Sprite() {
	animated = false;
}

Sprite::Sprite(const std::string& filePath) {
	if (!texture.loadFromFile(filePath))
		std::cout << "Could not load sprite at: " << filePath << std::endl;

	sprite.setTexture(texture);

	sprites.push_back(this);
}

Sprite::Sprite(const std::string& filePath, bool animated, bool random, int numFrames, int width, int height, float scale, int frequency, bool startAnimated)
	:Sprite(filePath)
{
	this->animated = animated;
	this->random = random;
	this->numFrames = numFrames;
	this->width = width;
	this->height = height;
	this->scale = scale;
	this->frequency = frequency;

	sprite.setScale(sf::Vector2f(scale, scale));
	if (startAnimated) {
		animating = true;
	}
	sprite.setTextureRect(sf::IntRect(offset * width, 0, width, height));
}

Sprite::Sprite(const std::string& filePath, bool animated, bool random, int numFrames, int width, int height, float scale, int frequency)
	:Sprite(filePath)
{
	this->animated = animated;
	this->random = random;
	this->numFrames = numFrames;
	this->width = width;
	this->height = height;
	this->scale = scale;
	this->frequency = frequency;

	sprite.setScale(sf::Vector2f(scale, scale));
	animating = true;
}

void Sprite::animate() {
	if (timer.getElapsedTime().asMilliseconds() >= frequency) {

		if (random) {
			offset = std::rand() % numFrames;
			sprite.setTextureRect(sf::IntRect(offset * width, 0, width, height));
		}
		else {
			sprite.setTextureRect(sf::IntRect(offset++ * width, 0, width, height));
			if (offset == numFrames) offset = 0;
		}

		//std::cout << "offset: " << offset << std::endl;

		timer.restart();
	}
}

void Sprite::animateOnce() {
	//if (timer.getElapsedTime().asMilliseconds() >= 1000) {
	sf::Clock tempTimer;
	tempTimer.restart();
		for (int i = 1; i <= numFrames; i++) {
			if (tempTimer.getElapsedTime().asMilliseconds() >= frequency) {
				sprite.setTextureRect(sf::IntRect(i * width, 0, width, height));
				tempTimer.restart();
			}
			
		}
		//timer.restart();
	//}
}

void Sprite::animateAll() {
	for (Sprite* s : sprites) {
		if (s->animated && s->animating) {
			s->animate();
		}
	}
}


sf::Sprite* Sprite::getSprite()
{
	return &sprite;
}

sf::Texture Sprite::getTexture()
{
	return texture;
}

sf::Clock Sprite::getTimer()
{
	return timer;
}

int Sprite::getWidth() {
	return width;
}

sf::FloatRect Sprite::getBoundingBox() {
	return sprite.getGlobalBounds();
}