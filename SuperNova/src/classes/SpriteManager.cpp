#include "headers/SpriteManager.h"


sf::Event event;
sf::Texture background;

SpriteManager::SpriteManager() {
	objects = new Object[];
}

void SpriteManager::animate() {
	for (int i = 0; i < numObjects; i++) {
		Object object = objects[i];

		int width = object.width;
		//sf::IntRect rectSourceSprite(0, 0, object.width, object.height);
		object.sprite.setTextureRect(sf::IntRect(0, 0, object.width, object.height));
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
}

/*void SpriteManager::init() {
	sf::Sprite sprite(background, sf::IntRect(0, 0, 1280, 768));
}*/

SpriteManager::Object SpriteManager::loadSprite(const std::string &filePath) {
	Object object = {this};

	if (!object.texture.loadFromFile(filePath))
		std::cout << "Could not load sprite at: " << filePath << std::endl;

	object.sprite.setTexture(object.texture);

	SpriteManager::objects[object.id] = object;

	return object;
}

void SpriteManager::loadSprite(const std::string &filePath, bool isAnimated, int numFrames, int width, int height, int frequency) {
	Object object = loadSprite(filePath);

	object.isAnimated = isAnimated;
	object.frequency = frequency;
	object.width = width;
	object.height = height;
	object.numFrames = numFrames;

	if (isAnimated) {
		object.animating = true;
	}

}