#include <headers/Player.h>
#include <SFML/Graphics.hpp>
#include <iostream>

float playerSpeed, playerSize, animationPerFrame = 1.0f / 8.0f;
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
	playerSpeed = 6.0f;
	//playerSprite.setPosition(64 * 5, 64 * 9);
	playerSprite.setPosition(64 * startPosition.x, 64 * startPosition.y);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 834, 1666));
	x = startPosition.x * 64;
	y = startPosition.y * 64;
	
	//this is the Size of the player
	playerSize = 0.077f;

	//setting the initial size of the player.
	playerSprite.setScale(playerSize, playerSize);
	
	if (!texture.loadFromFile("src/resources/astronaut_walk.png")) {
		std::cout << "Could not load astronaut texture" << std::endl;
	}
	playerSprite.setTexture(texture);

	//the set Origin will put a "point" in the middle of the sprite and the sprite will now rotate around that point when manipulated.
	playerSprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
}

// 
// Checks if A or D is pressed and moves left or right respectively
// ( Movement is animated on a ratio (set by the variable animationPerFrame) )
//
void Player::checkMovement() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (checkCollision(playerSpeed)) {
			x += playerSpeed;
			playerSprite.move(playerSpeed, 0);
			//the sprite size in sprite sheet is 800x1600. this tells textureRect to start at beginning and every time walkCount is added, then it goes to next frame
			playerSprite.setTextureRect(sf::IntRect(offset * 834, 0, 834, 1668));
		}
		
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if(checkCollision(-playerSpeed)){
			x -= playerSpeed;
			playerSprite.move(-playerSpeed, 0);
			//the left facing frames are at 800*2 x 1600 so this tells does same as above but lower on the sprite sheet
			playerSprite.setTextureRect(sf::IntRect(offset * 834, 834 * 2, 800, 1668));
		}
		

	}

	frameCount++;
	if ((int)(frameCount * animationPerFrame) > offset) offset++;

	//There are 8 frames for walking now, this allows each frame to cycle and then reset when the last frame is projected onto the screen
	if (offset == 8) {
		frameCount = 0;
		offset = 0;
	}

	
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(playerSprite);
}

void Player::respawn() {
	playerSprite.setPosition(64 * startPosition.x, 64 * startPosition.y);
}

void Player::update() {
	checkMovement();
}

bool Player::checkCollision(float velo) {
	//playerSprite.move(playerSpeed, 0);
	//std::cout << "Global bounds " << playerSprite.getGlobalBounds().height << " " << playerSprite.getGlobalBounds().width;;
	//std::cout << "Local bounds " << playerSprite.getLocalBounds().height << playerSprite.getLocalBounds().width;
	std::cout << "Current Position " << playerSprite.getPosition().x << " " << playerSprite.getPosition().y << "\n";
	float nx = x + velo;
	std::cout << "Future position " << nx << "\n";
	if (nx >= 448 || nx < 256) {
		return false;
	}
	return true;
}