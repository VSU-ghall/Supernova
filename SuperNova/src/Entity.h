#pragma once
#include <string>

/*
	Entiy class idea originated from the following lecture: https://www.youtube.com/watch?v=4_DKdliZv_4&list=PL_xRyXins848jkwC9Coy7B4N5XTOnQZzz&index=5
*/

class Entity
{

private:

	//Since the constructor is private EntityManager class needs this to create Entities
	friend class EntityManager;

	size_t id = 0; //unique id of the entity
	std::string tag = "default"; //tag to allow similar entities to be gathered
	bool isActive = true; //true if the entity is alive false if entity is dead

	Entity(const size_t& id, const std::string& tag); //constructor requries a unique unsigned int as id and tag

public:
	
	bool getIsActive();
	std::string& getTag();
	size_t getId();
	void destroy(); //sets isActive to false
};

