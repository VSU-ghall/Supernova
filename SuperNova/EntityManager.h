#include <cstdint>
#include <vector>
#include <map>
#pragma once

//Define an entity as an ID
using Entity = std::uint32_t;
//Max number of entities
//const Entity MAX_ENTITIES = 5000;


class EntityManager
{
private:
	std::vector<Entity> entities;
	std::map<Entity> entityMap;
public:
	EntityManager() {}

	Entity createEntity();

	void deleteEntity(Entity entity);
};

