#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Entity.h"
#pragma once

//entityVector holds all entities
typedef std::vector<std::shared_ptr<Entity>> EntityVector;

//String is tag. Each vector hold entities that share that tag.
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
private:

	EntityVector entities;
	EntityMap entityMap;
	size_t numEntities = 0;

	void removeDeadEntites(EntityVector& vector);

public:
	EntityManager() {}

	void update();

	std::shared_ptr<Entity> addEntity(const std::string& tag);
	const EntityVector& getEntities();
	const EntityVector& getEntites(const std::string& tag);
	size_t getNumEntities();

};

