#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

float playerSpeed, playerSize, animationPerFrame = 1.0f / 5.0f;
int frameCount = 0, offset = 0;

sf::Sprite playerSprite;
sf::Texture texture;

float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

void Player::init() {
	
	//this is how fast we want the player. If we want to change their speed this can be changed.
	playerSpeed = 10.0f;
	playerSprite.move(128,128);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 795, 1595));
	
	//this is the Size of the player
	playerSize = 0.08f;

	//setting the initial size of the player.
	playerSprite.setScale(playerSize, playerSize);
	if (!texture.loadFromFile("src/img/astronaut_walk.png")) {
		std::cout << "Could not load astronaut texture" << std::endl;
	}
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

// 
// Checks if A or D is pressed and moves left or right respectively
// ( Movement is animated on a ratio (set by the variable animationPerFrame) )
//
void Player::checkMovement() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerSprite.move(playerSpeed, 0);
		//the sprite size in sprite sheet is 800x1600. this tells textureRect to start at beginning and every time walkCount is added, then it goes to next frame
		playerSprite.setTextureRect(sf::IntRect(offset * 800, 0, 800, 1600));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		playerSprite.move(-playerSpeed, 0);
		//the left facing frames are at 800*2 x 1600 so this tells does same as above but lower on the sprite sheet
		playerSprite.setTextureRect(sf::IntRect(offset * 800, 800 * 2, 800, 1600));

	}

	frameCount++;
	if ((int)(frameCount * animationPerFrame) > offset) offset++;

	//Since there are only 4 frames atm, this allows the frames to reach the end, then start again
	if (offset == 4) {
		frameCount = 0;
		offset = 0;
	}

	
}