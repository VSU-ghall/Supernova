#include "headers/Entity.h"
#include <headers/Sprite.h>

Entity::Entity(const size_t& id, const std::string& tag)
	:id(id), tag(tag)
{}

Entity::Entity(const size_t& id, const std::string& tag, Sprite *s, sf::Vector2f pos)
	: id(id), tag(tag), sprite(s), position(pos)
{}

bool Entity::getIsActive() {
	return isActive;
}

std::string& Entity::getTag() {
	return tag;
}

size_t Entity::getId() {
	return id;
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