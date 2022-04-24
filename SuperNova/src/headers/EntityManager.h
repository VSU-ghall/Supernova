#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Entity.h"
#include <list>
#pragma once

/***
Entity Manager class idea came from the following lecture: https://www.youtube.com/watch?v=6zWCSSybS50&list=PL_xRyXins848jkwC9Coy7B4N5XTOnQZzz&index=8.
The lecture provided an idea of how to structure the code and methods, but the code in the methods is original.
***/

//entityVector holds all entities
typedef std::list<std::shared_ptr<Entity>> EntityVector;

//String is tag. Each vector hold entities that share that tag.
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
private:

	EntityVector entities; //all entities currently alive
	EntityVector entitiesToAdd; //entities that are ready to be added to entities
	EntityMap entityMap; //map that stores vectors. each vector stores entities that share the same tag
	size_t numEntities = 0; //unsigned int used to create unique entity ids
	EntityVector entitiesInteractable;
	EntityMap entityMapInteractable;
	EntityVector dynamicEntities;

	void removeDeadEntities(EntityVector& vector); //helper method that iterates through a given vector and removes any entities that are not alive
	void removeUninteractableEntities(EntityVector& vector);

public:
	EntityManager();

	void update(); //method updates EntityManager to add new entities and remove dead entities

	std::shared_ptr<Entity> addEntity(const std::string& tag, const std::string& type); //creates and returns an entity with the tag provided
	std::shared_ptr<Entity> addEntity(Entity e);
	const EntityVector& getEntities(); //returns a vector containing all entities that are currently alive
	const EntityVector& getEntitiesInteractable();
	const EntityVector& getEntities(const std::string& tag); //returns a vector containing all entities that share the tag parameter
	const EntityVector& getInteractableEntities(const std::string& tag);
	size_t getNumEntities();

};

