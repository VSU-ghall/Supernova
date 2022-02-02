#include "EntityManager.h"

EntityManager::EntityManager() {

}

Entity EntityManager::createEntity(){
	Entity id = entities.size();
	entities.assign(1, id);
	return id;
}

void EntityManager::deleteEntity(Entity entity) {

}
