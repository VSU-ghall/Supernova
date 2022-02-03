#include "Player.h"
#include <GL/glut.h>
#include <SFML/Graphics.hpp>
#include <iostream>

float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

void Player::update() {

}

void Player::draw(sf::RenderWindow& window) {

	sf::Texture texture;
	if (!texture.loadFromFile("src/img/astronaut.png")) {
		std::cout << "Could not load astronaut texture" << std::endl;
		//return NULL;
	}

	sf::Sprite playerSprite;
	playerSprite.setTexture(texture);

	//playerSprite.setPosition(sf::Vector2f(100, 100));
	//playerSprite.scale(sf::Vector2f(1, 0.5));

	window.draw(playerSprite);
}