#include "headers/Entity.h"
#include <headers/Sprite.h>

Entity::Entity(const std::string& tag) 
	: tag(tag) {}

Entity::Entity(const std::string& tag, Sprite *s, sf::Vector2f pos)
	: Entity(tag) 
{
	sprite = s; position = pos;

	sprite->getSprite()->setPosition(position);

	float area = (sprite->getScaledSize().x * sprite->getScaledSize().y) / (64 * 64); // gives # squares it takes up

	damageDealt = area * 0.125 + 0.2; //remove the "+ 0.2" on easy difficulty
}

Entity::Entity(const std::string& tag, Sprite* s, sf::Vector2f pos, sf::Vector2f pos2)
	: Entity(tag, s, pos)
{
	dynamic = true;
	position2 = pos2;

	if (position.x > position2.x) {
		position2 = position;
		position = pos2;
	}

	sprite->getSprite()->setPosition(position);
	speed = 1 + 150.0f / sprite->getFrequency() + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	cooldownTime = sf::Time(sf::seconds(0.5));
}

bool Entity::getIsActive() {
	return isActive;
}

sf::Time Entity::getCooldown() {
	return cooldownTime;
}

float Entity::getDamageDealt() {
	return damageDealt;
}

Entity::Direction Entity::getDirection() {
	return direction;
}

void Entity::reverseDirection() {
	if (direction == right) direction = left;
	else direction = right;

	sprite->flipHorizontal();
}

void Entity::takeDamage() {
	if (!dynamic) return;

	float area = (sprite->getScaledSize().x * sprite->getScaledSize().y) / (64 * 64); // gives # squares it takes up

	float damage = 1 - (area * 0.125 + 0.3); //remove the "+ 0.3" on easy difficulty

	health -= damage;

	if (sprite->hasDamaged()) sprite->animateDamaged();

	if (health <= 0) destroy();
}

void Entity::attack() {
	if (sprite->hasSpecial()) sprite->animateSpecial();
	cooldown = true;
	cooldownTimer.restart();
}

std::string& Entity::getTag() {
	return tag;
}

bool Entity::isInCooldown() {
	return cooldown;
}

void Entity::isInCooldown(bool cooldown) {
	this->cooldown = cooldown;
}

bool Entity::isDynamic() {
	return dynamic;
}

void Entity::destroy() {
	Sprite::remove(sprite);
	isActive = false;
}

Sprite* Entity::getSprite(){
	return sprite;
}

float Entity::getSpeed() {
	return speed;
}

sf::Vector2f Entity::getCurrentPosition() {
	return sprite->getSprite()->getPosition();
}

sf::Vector2f Entity::getPosition() {
	return position;
}

sf::Vector2f Entity::getPosition2() {
	return position2;
}

void Entity::notInteractable() {
	isInteractable = false;
}

bool Entity::getIsInteractable() {
	return isInteractable;
}

void Entity::setCooldown(sf::Time time) {
	cooldownTime = time;
}