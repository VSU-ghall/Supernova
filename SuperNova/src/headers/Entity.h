#pragma once
#include <string>
#include <vector>
#include "Components.h"
#include <headers/Sprite.h>

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
	Sprite *sprite;
	std::vector<Component> components;
	sf::Vector2f position;

	Entity(const size_t& id, const std::string& tag); //constructor requries a unique unsigned int as id and tag
	Entity(const size_t& id, const std::string& tag, Sprite* s, sf::Vector2f pos);

public:
	
	bool getIsActive();
	std::string& getTag();
	size_t getId();
	void destroy(); //sets isActive to false
	Sprite* getSprite();
	sf::Vector2f getPosition();

	//template <typename T>
	//bool hasComponent() {
	//	return getComponent<T>().has;
	//}

//	template<typename T>
//	T & getComponent() {
//		//return std::get<T>(components);
//		//return std::get<T>(components);
//		for (auto& c : components) {
//			if (c == std::forward<T>) {
//				return c;
//			}
//		}
//		//return nullptr;
//	}
//
//	//template<typename T>
//	template <typename T, typename...TArgs>
////	T & addComponent(TArgs&&... mArgs){
//	void addComponent(TArgs&&...mArgs){
//	//void addComponent(Component c){
////		auto & component = getComponent<T>();
////		component = T(std::forward<TArgs>(mArgs)...);
////		component.has = true;
//		components.push_back(std::forward<TArgs>(mArgs)...);
////		return TArgs;
//	}
	


};

