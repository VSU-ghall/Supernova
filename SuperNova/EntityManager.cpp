#include "EntityManager.h"

EntityManager::EntityManager() {

}

void EntityManager::update() {
	//Needs to be implemented.
}

void EntityManager::removeDeadEntites(EntityVector& vector) {
	for (auto iterator = vector.begin(); iterator != vector.end(); iterator++) {
		auto e = *iterator;
		if (e->getIsActive() == false) {
			vector.erase(iterator--);
		}
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {
	auto entity = std::shared_ptr<Entity>(new Entity(numEntities++, tag));
	entitiesToAdd.push_back(entity);
	return entity;

}

const EntityVector& EntityManager::getEntities() {
	return entities;
}

const EntityVector& EntityManager::getEntites(const std::string& tag) {
	//Needs to be implemented. Returns correct vector from map.
}

size_t EntityManager::getNumEntities() {
	return numEntities;
}
