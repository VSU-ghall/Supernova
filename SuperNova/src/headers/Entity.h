#pragma once
#include <string>
#include <vector>
#include <headers/Sprite.h>

/*
	Entiy class idea originated from the following lecture: https://www.youtube.com/watch?v=4_DKdliZv_4&list=PL_xRyXins848jkwC9Coy7B4N5XTOnQZzz&index=5
*/

class Entity
{
public:

	enum Direction { right, left };
	sf::Clock cooldownTimer;

	Entity(const std::string& tag); //constructor requries a unique unsigned int as id and tag
	Entity(const std::string& tag, Sprite* s, sf::Vector2f pos); //constructor for static entity
	Entity(const std::string& tag, Sprite* s, sf::Vector2f pos, sf::Vector2f pos2); //constructor for dynamic entity
	
	void attack();
	bool getIsActive();
	std::string& getTag();
	bool isInCooldown();
	void isInCooldown(bool cooldown);
	bool isDynamic();
	void destroy(); //sets isActive to false
	sf::Time getCooldown();
	float getDamageDealt();
	Direction getDirection();
	void reverseDirection();
	Sprite* getSprite();
	float getSpeed();
	sf::Vector2f getCurrentPosition();
	sf::Vector2f getPosition();
	sf::Vector2f getPosition2();
	void notInteractable();
	bool getIsInteractable();

	void setCooldown(sf::Time time);

private:

	bool dynamic = false; //dynamic or static enemy
	std::string tag = "default"; //tag to allow similar entities to be gathered
	bool isActive = true; //true if the entity is alive false if entity is dead
	Sprite* sprite;
	sf::Vector2f position, position2;
	bool isInteractable = true, cooldown = false;
	float speed, damageDealt;
	sf::Time cooldownTime;
	Direction direction = right;

};

