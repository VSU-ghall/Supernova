#include "EntityManager.h"

EntityManager::EntityManager() {

}

void EntityManager::update() {
	//Add entities to proper location
		//Add to vector of all entities
		//Add them to vector inside of map
	for (auto& e : entitiesToAdd) {
		entities.push_back(e);
		entityMap.find(e->getTag())->second.push_back(e);

	}
		
	//remove dead entities from entities
	removeDeadEntities(entities);

	//remove dead entities from vector in map
	for (auto & v : entityMap) {
		removeDeadEntities(v.second);
	}
}

void EntityManager::removeDeadEntities(EntityVector& vector) {
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
	EntityMap::iterator it;
	it = entityMap.find(tag);
	if (it == entityMap.end()) {
		return;
	}
	else {
		return it->second;
	}
}

size_t EntityManager::getNumEntities() {
	return numEntities;
}
