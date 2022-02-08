#include "EntityManager.h"

EntityManager::EntityManager() 
{

}

//method updates EntityManager to add new entities and remove dead entities
void EntityManager::update() {
	//Add to vector of all entities and Add them to vector inside of map
	for (auto& e : entitiesToAdd) {
		entities.push_back(e);
		entityMap[e->getTag()].push_back(e);
	}

	entitiesToAdd.clear();
		
	//remove dead entities from entities
	removeDeadEntities(entities);

	//remove dead entities from vector in map
	for (auto & v : entityMap) {
		removeDeadEntities(v.second);
	}
}

//helper method that iterates through a given vector and removes any entities that are not alive
void EntityManager::removeDeadEntities(EntityVector& vector) {
	for (auto iterator = vector.begin(); iterator != vector.end(); iterator++) {
		auto e = *iterator;
		if (e->getIsActive() == false) {
			vector.erase(iterator);
			if (!vector.empty()) {
				iterator--;
			}
			else {
				break;
			}
		}
	}
}

//creates and returns an entity with the tag provided
std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {
	auto entity = std::shared_ptr<Entity>(new Entity(numEntities++, tag));
	entitiesToAdd.push_back(entity);
	return entity;

}

//returns a vector containing all entities that are currently alive
const EntityVector& EntityManager::getEntities() {
	return entities;
}

//returns a vector containing all entities that share the tag parameter
const EntityVector& EntityManager::getEntities(const std::string& tag) {
	EntityMap::iterator it;
	it = entityMap.find(tag);
	return it->second;
}

size_t EntityManager::getNumEntities() {
	return numEntities;
}
