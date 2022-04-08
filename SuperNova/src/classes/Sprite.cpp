#include "headers/Sprite.h"

Sprite::Sprite() {
	animated = false;
}

Sprite::Sprite(const std::string& filePath) {
	if (!texture.loadFromFile(filePath))
		std::cout << "Could not load sprite at: " << filePath << std::endl;

	sprite.setTexture(texture);
	this->filePath = filePath;

	sprites.push_back(this);
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
	if (animated) animating = true;

	if (!animated) sprite.setTextureRect(sf::IntRect(0,0, width, height));
}

void Sprite::animate() {
	if (timer.getElapsedTime().asMilliseconds() >= frequency) {

		if (random) {
			offset = std::rand() % numFrames;
			sprite.setTextureRect(sf::IntRect(offset * width, 0, width-boundWidth, height-boundHeight));
		}
		else {
			sprite.setTextureRect(sf::IntRect(offset++ * width, 0, width-boundWidth, height-boundHeight));
			if (offset == numFrames) offset = 0;
		}

		//std::cout << "offset: " << offset << std::endl;

		timer.restart();
	}
}

void Sprite::animateOnce() {
	if (!animating) animating = true;
	if (timer.getElapsedTime().asMilliseconds() >= frequency) {

		sprite.setTextureRect(sf::IntRect(offset++ * width, 0, width, height));
		if (offset == numFrames) {
			offset = 0;
			animating = false;
		}

		//std::cout << "offset: " << offset << std::endl;

		timer.restart();
	}
}

void Sprite::animateAll() {
	for (Sprite* s : sprites) {
		if (s->animated && s->animating) {
			s->animate();
		}

		if (!s->animated && s->animating) {
			if (s->offset != s->numFrames) s->animateOnce();
		}
	}
}

std::string& Sprite::getFilePath() { return filePath; }

int Sprite::getFrequency() { return frequency; }

int Sprite::getHeight() { return height; }

int Sprite::getNumFrames() { return numFrames;  }

float Sprite::getScale() { return scale; }

sf::Sprite* Sprite::getSprite() { return &sprite; }

sf::Texture Sprite::getTexture() { return texture; }

sf::Clock Sprite::getTimer() { return timer; }

int Sprite::getWidth() { return width; }

sf::FloatRect Sprite::getBoundingBox() { return sprite.getGlobalBounds(); }

bool Sprite::isAnimated() { return animated; }

bool Sprite::isRandom() { return random; }

void Sprite::setBounds(int width, int height) {
	boundWidth = floor(floor(scale*this->width - width) / scale);
	boundHeight = ceil((ceil(scale * this->height) - height) / scale);
}