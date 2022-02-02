#include <cstdint>
#include <vector>
#pragma once

//Define an entity as an ID
using Entity = std::uint32_t;
//Max number of entities
//const Entity MAX_ENTITIES = 5000;


class EntityManager
{
private:
	std::vector<Entity> entities;
public:
	EntityManager() {}

	Entity createEntity();

	void deleteEntity(Entity entity);
};

