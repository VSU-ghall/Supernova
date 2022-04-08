#include "headers\Object.h"

Object::Object(int index, Sprite* sprite) {
	this->sprite = sprite; this->index = index;
}

Sprite* Object::getObject() { return sprite; }
Sprite* Object::getIcon() { return icon; }
int Object::getIndex() { return index; }
sf::Vector2i Object::getSize() { return sf::Vector2i(sprite->getTexture().getSize().x * sprite->getScale(),
														sprite->getTexture().getSize().y * sprite->getScale()); }	
bool Object::isHidden() { return hidden; }
bool Object::hasHiddenIcon() { return hiddenIcon; }
bool Object::hasIcon() { return boolIcon; }

void Object::activateIcon() {
	icon->getSprite()->setColor(sf::Color(255, 255, 255, 255));
	hiddenIcon = false;
}

void Object::collect() {
	if (boolIcon) deactivateIcon();
	hide();
}

void Object::deactivateIcon() {
	icon->getSprite()->setColor(sf::Color(100, 100, 100, 255));
	hiddenIcon = false;
}

void Object::hide() {
	sprite->getSprite()->setColor(sf::Color(255, 255, 255, 0));
	hidden = true;
}

void Object::hideIcon() {
	icon->getSprite()->setColor(sf::Color(255, 255, 255, 0));
	hiddenIcon = true;
}

void Object::setIcon(bool boolIcon) {
	this->boolIcon = boolIcon;

	if (boolIcon) {
		icon = new Sprite(sprite->getFilePath(), sprite->isAnimated(), sprite->isRandom(), sprite->getNumFrames(), sprite->getWidth(), sprite->getHeight(), sprite->getScale(), sprite->getFrequency());
		hideIcon();
	}
}

void Object::show() {
	sprite->getSprite()->setColor(sf::Color(255, 255, 255, 255));
	hidden = false;
}