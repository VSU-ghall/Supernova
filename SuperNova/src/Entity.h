#pragma once
#include <string>
class Entity
{

private:

	//Since the constructor is private EntityManager class needs this to create Entities
	friend class EntityManager;

	size_t id = 0; //unique id of the entity
	std::string tag = "default"; //tag to allow similar entities to be gathered
	bool isActive = true; 

	Entity(const size_t& id, const std::string& tag);

public:
	
	bool getIsActive();
	std::string& getTag();
	size_t getId();
	void destroy();
};

