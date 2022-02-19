#include "headers/Sprite.h"

Sprite::Sprite() {

}

Sprite::Sprite(const std::string& filePath){
	if (!texture.loadFromFile(filePath))
		std::cout << "Could not load sprite at: " << filePath << std::endl;
	
	sprite.setTexture(texture);
}

Sprite::Sprite(const std::string& filePath, bool isAnimated, int numFrames, int width, int height, int frequency) {
	Sprite::Sprite(filePath);

	this->animated = isAnimated;
	this->numFrames = numFrames;
	this->width = width;
	this->height = height;
	this->frequency = frequency;
}

/*void SpriteManager::animate() {
	for (int i = 0; i < numSprites; i++) {
		Sprite sprite = sprites[i];

		int width = sprite.getWidth();
		//sf::IntRect rectSourceSprite(0, 0, object.width, object.height);
		sprite.getSprite().setTextureRect(sf::IntRect(0, 0, width, object.height));
		if (object.animating && object.timer.getElapsedTime().asMilliseconds() >= object.frequency) {
			//next frame
			width += object.width;

			if (width >= object.width * object.numFrames){
				width = object.width;
				object.timer.restart();
			}
			else
				object.sprite.setTextureRect(sf::IntRect(0, 0, object.width, object.height));
		}
	}
}*/

bool Sprite::isAnimating()
{
	return animating;
}

void Sprite::isAnimating(bool boolean) {
	animating = boolean;
}

bool Sprite::isAnimated()
{
	return animated;
}

sf::Sprite Sprite::getSprite()
{
	return sprite;
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