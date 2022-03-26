#include "headers/Entity.h"
#include <headers/Sprite.h>

Entity::Entity(const size_t& id, const std::string& tag)
	:id(id), tag(tag)
{}

Entity::Entity(const size_t& id, const std::string& tag, Sprite *s)
	: id(id), tag(tag), sprite(s)
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