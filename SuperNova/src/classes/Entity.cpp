#include "headers/Entity.h"
#include <headers/Sprite.h>

Entity::Entity(const std::string& tag) 
	: tag(tag) {}

Entity::Entity(const std::string& tag, Sprite *s, sf::Vector2f pos)
	: Entity(tag) 
{
	sprite = s; position = pos;

	sprite->getSprite()->setPosition(position);
}

Entity::Entity(const std::string& tag, Sprite* s, sf::Vector2f pos, sf::Vector2f pos2)
	: Entity(tag, s, pos)
{
	dynamic = true;
	position2 = pos2;

	if (position.x > position2.x) {
		sf::Vector2f temp = position;
		position = position2;
		position2 = temp;
	}

	sprite->getSprite()->setPosition(position);
	speed = sprite->getFrequency() / 64.0f;
}

bool Entity::getIsActive() {
	return isActive;
}

Entity::Direction Entity::getDirection() {
	return direction;
}

void Entity::reverseDirection() {
	if (direction == right) direction = left;
	else direction = right;

	sprite->flip();
}

std::string& Entity::getTag() {
	return tag;
}

bool Entity::isDynamic() {
	return dynamic;
}

void Entity::destroy() {
	isActive = false;
}

Sprite* Entity::getSprite(){
	return sprite;
}

float Entity::getSpeed() {
	return speed;
}

sf::Vector2f Entity::getCurrentPosition() {
	return sprite->getSprite()->getPosition();
}

sf::Vector2f Entity::getPosition() {
	return position;
}

sf::Vector2f Entity::getPosition2() {
	return position2;
}

void Entity::notInteractable() {
	isInteractable = false;
}

bool Entity::getIsInteractable() {
	return isInteractable;
}