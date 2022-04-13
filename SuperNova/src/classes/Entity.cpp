#include "headers/Entity.h"
#include <headers/Sprite.h>

Entity::Entity(const std::string& tag) 
	: tag(tag) {}

Entity::Entity(const std::string& tag, Sprite *s, sf::Vector2f pos)
	: Entity(tag) 
{
	sprite = s; position = pos;
}

Entity::Entity(const std::string& tag, Sprite* s, sf::Vector2f pos, sf::Vector2f pos2)
	: Entity(tag, s, pos)
{
	position2 = pos2;
}

bool Entity::getIsActive() {
	return isActive;
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

sf::Vector2f Entity::getPosition() {
	return position;
}

void Entity::notInteractable() {
	isInteractable = false;
}

bool Entity::getIsInteractable() {
	return isInteractable;
}