#include "headers\Object.h"

Object::Object(int index, int iconIndex, Sprite* sprite, sf::Vector2f pos) {
	this->index = index; this->iconIndex = iconIndex; this->sprite = sprite;

	sprite->getSprite()->setPosition(pos);
}

Sprite* Object::getObject() { return sprite; }
Sprite* Object::getIcon() { return icon; }
int Object::getIconIndex() { return iconIndex; }
int Object::getIndex() { return index; }
sf::Vector2i Object::getSize() { return sf::Vector2i(sprite->getTexture().getSize().x * sprite->getScale(),
														sprite->getTexture().getSize().y * sprite->getScale()); }	
bool Object::isBullet() { return bullet; }
void Object::isBullet(bool bullet) { this->bullet = bullet; }
bool Object::isCollectible() { return collectible; }
void Object::isCollectible(bool collectible) { this->collectible = collectible; }
bool Object::isGoingLeft() { return !right; }
bool Object::isGoingRight() { return right; }
void Object::isGoingRight(bool right) { this->right = right; }
bool Object::isHealthPack() { return healthPack; }
void Object::isHealthPack(bool healthPack) { this->healthPack = healthPack; }
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

// Adapted code from: https://stackoverflow.com/questions/27306086/c-remove-object-from-vector
void Object::removeSprite() {
	Sprite::remove(sprite);
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