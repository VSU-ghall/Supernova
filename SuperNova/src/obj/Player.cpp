#include "Player.h"
#include <GL/glut.h>
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Sprite playerSprite;
float playerSpeed;
float playerSize;
float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

void Player::update() {

}
void Player::init() {
	

	//this is how fast we want the player. If we want to change there speed this can be changed.
	playerSpeed = .25f;
	playerSprite.setPosition(160, 160);
	
	//this is the Size of the player
	playerSize = .25f;

	//setting the initial size of the player.
	playerSprite.setScale(playerSize, playerSize);
}

void Player::draw(sf::RenderWindow& window) {

	sf::Texture texture;
	if (!texture.loadFromFile("src/img/astronaut.png")) {
		std::cout << "Could not load astronaut texture" << std::endl;
		//return NULL;
	}

	
	playerSprite.setTexture(texture);
	//the set Origin will put a "point" in the middle of the sprite and the sprite will now rotate around that point when manipulated.
	playerSprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
	


	window.draw(playerSprite);
}
//the checkMovment Checks if A or D is pressed and if it is the player will move left or right depending on what is pressed
void Player::checkMovment() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerSprite.move(playerSpeed, 0);
		playerSprite.setScale(playerSize, playerSize);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		playerSprite.move(-playerSpeed, 0);
		playerSprite.setScale(-playerSize, playerSize);
	}
}