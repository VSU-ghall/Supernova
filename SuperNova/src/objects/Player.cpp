#include "Player.h"
#include <GL/glut.h>
#include <SFML/Graphics.hpp>
#include <iostream>

float playerSpeed, playerSize, animationPerFrame = 1.0f / 5.0f;
int frameCount = 0, offset = 0;

sf::Sprite playerSprite;
<<<<<<< HEAD:SuperNova/src/obj/Player.cpp
float playerSpeed;
float playerSize;
=======
sf::Texture texture;

>>>>>>> db3e313d0918083fdbd5ce186a7397541b574211:SuperNova/src/objects/Player.cpp
float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

void Player::init() {
	
<<<<<<< HEAD:SuperNova/src/obj/Player.cpp

	//this is how fast we want the player. If we want to change there speed this can be changed.
	playerSpeed = 1.0f;
	playerSprite.setPosition(192, 256);
=======
	//this is how fast we want the player. If we want to change their speed this can be changed.
	playerSpeed = 10.0f;
	playerSprite.move(64 * 3,64 * 11);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 795, 1595));
>>>>>>> db3e313d0918083fdbd5ce186a7397541b574211:SuperNova/src/objects/Player.cpp
	
	//this is the Size of the player
	playerSize = 1.0f;

	//setting the initial size of the player.
	playerSprite.setScale(playerSize, playerSize);
<<<<<<< HEAD:SuperNova/src/obj/Player.cpp
}

void Player::draw(sf::RenderWindow& window) {

	sf::Texture texture;
	if (!texture.loadFromFile("src/img/astronaut.png")) {
		std::cout << "Could not load astronaut texture" << std::endl;
		//return NULL;
	}

	
=======
	if (!texture.loadFromFile("src/resources/astronaut_walk.png")) {
		std::cout << "Could not load astronaut texture" << std::endl;
	}
>>>>>>> db3e313d0918083fdbd5ce186a7397541b574211:SuperNova/src/objects/Player.cpp
	playerSprite.setTexture(texture);

	//the set Origin will put a "point" in the middle of the sprite and the sprite will now rotate around that point when manipulated.
	playerSprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
}

void Player::update() {
	checkMovement();
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(playerSprite);
}
<<<<<<< HEAD:SuperNova/src/obj/Player.cpp
//the checkMovment Checks if A or D is pressed and if it is the player will move left or right depending on what is pressed
void Player::checkMovment() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerSprite.move(playerSpeed, 0);
		playerSprite.setScale(playerSize, playerSize);
=======

// 
// Checks if A or D is pressed and moves left or right respectively
// ( Movement is animated on a ratio (set by the variable animationPerFrame) )
//
void Player::checkMovement() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerSprite.move(playerSpeed, 0);
		//the sprite size in sprite sheet is 800x1600. this tells textureRect to start at beginning and every time walkCount is added, then it goes to next frame
		playerSprite.setTextureRect(sf::IntRect(offset * 800, 0, 800, 1600));
>>>>>>> db3e313d0918083fdbd5ce186a7397541b574211:SuperNova/src/objects/Player.cpp
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		playerSprite.move(-playerSpeed, 0);
<<<<<<< HEAD:SuperNova/src/obj/Player.cpp
		playerSprite.setScale(-playerSize, playerSize);
=======
		//the left facing frames are at 800*2 x 1600 so this tells does same as above but lower on the sprite sheet
		playerSprite.setTextureRect(sf::IntRect(offset * 800, 800 * 2, 800, 1600));

	}

	frameCount++;
	if ((int)(frameCount * animationPerFrame) > offset) offset++;

	//Since there are only 4 frames atm, this allows the frames to reach the end, then start again
	if (offset == 4) {
		frameCount = 0;
		offset = 0;
>>>>>>> db3e313d0918083fdbd5ce186a7397541b574211:SuperNova/src/objects/Player.cpp
	}
}