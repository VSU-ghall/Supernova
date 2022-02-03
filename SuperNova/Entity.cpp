#include "Entity.h"

Entity::Entity(const size_t& id, const std::string& tag)
	:id(id), tag(tag)
{}

bool Entity::getIsActive() {
	return isActive;
}

std::string& Entity::getTag() {
	return tag;
}

size_t& Entity::getId() {
	return id;
}

void Entity::destroy() {
	isActive = false;
}