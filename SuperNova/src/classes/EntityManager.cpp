#include "headers/EntityManager.h"

EntityManager::EntityManager() 
{

}

//method updates EntityManager to add new entities and remove dead entities
void EntityManager::update() {
	//Add to vector of all entities and Add them to vector inside of map
	for (auto& e : entitiesToAdd) {
		entities.push_back(e);
		entityMap[e->getTag()].push_back(e);
		entitiesInteractable.push_back(e);
		entityMapInteractable[e->getTag()].push_back(e);
		if (e->isDynamic()) dynamicEntities.push_back(e);
	}

	entitiesToAdd.clear();
		
	//remove dead entities from entities
	removeDeadEntities(entities);
	removeUninteractableEntities(entitiesInteractable);

	//remove dead entities from vector in map
	for (auto & v : entityMap) {
		removeDeadEntities(v.second);
	}

	for (auto& v : entityMapInteractable) {
		removeUninteractableEntities(v.second);
		removeDeadEntities(v.second);
	}

	//move dynamic enemies
	for (auto &e : dynamicEntities) {
		if (e->getSprite()->animatingSpecial || e->getSprite()->animatingDamaged) continue;

		if (e->isInCooldown() && e->cooldownTimer.getElapsedTime() >= e->getCooldown()) e->isInCooldown(false);

		sf::Vector2f currentPosition = e->getCurrentPosition();

		if (currentPosition.x > e->getPosition2().x ||
			currentPosition.x < e->getPosition().x) {
			e->reverseDirection();
		}

		if (e->getDirection() == Entity::Direction::right) {
			currentPosition.x += e->getSpeed();
		}
		else {
			currentPosition.x -= e->getSpeed();
		}

		e->getSprite()->getSprite()->setPosition(currentPosition);
	}
}

//helper method that iterates through a given vector and removes any entities that are not alive
void EntityManager::removeDeadEntities(EntityVector& vector) {
	std::list<std::shared_ptr<Entity>>::iterator i = vector.begin();
	while (i != vector.end()) {
		if (i->get()->getIsActive() == false) {
			vector.erase(i++); 
		}
		else {
			i++;
		}
	}
}

void EntityManager::removeUninteractableEntities(EntityVector& vector) {
	std::list<std::shared_ptr<Entity>>::iterator i = vector.begin();
	while (i != vector.end()){
		if (i->get()->getIsInteractable() == false){
			vector.erase(i++); 
		}
		else {
			i++;
		}
	}
}

//creates and returns an entity with the tag provided
std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {
	auto entity = std::shared_ptr<Entity>(new Entity(tag));
	entitiesToAdd.push_back(entity);
	return entity;

}

//creates and returns an entity with the tag provided
std::shared_ptr<Entity> EntityManager::addEntity(Entity e) {
	auto entity = std::make_shared<Entity>(std::move(e));
	entitiesToAdd.push_back(entity);
	numEntities++;
	return entity;

}

//returns a vector containing all entities that are currently alive
const EntityVector& EntityManager::getEntities() {
	return entities;
}

const EntityVector& EntityManager::getEntitiesInteractable() {
	return entitiesInteractable;
}

//returns a vector containing all entities that share the tag parameter
const EntityVector& EntityManager::getEntities(const std::string& tag) {
	EntityMap::iterator it;
	it = entityMap.find(tag);
	return it->second;
}

const EntityVector& EntityManager::getInteractableEntities(const std::string& tag) {
	EntityMap::iterator it;
	it = entityMapInteractable.find(tag);
	if (it != entityMapInteractable.end()) {
		return it->second;
	}
	else {
		EntityVector empty;
		return empty;
	}
}

size_t EntityManager::getNumEntities() {
	return numEntities;
}
