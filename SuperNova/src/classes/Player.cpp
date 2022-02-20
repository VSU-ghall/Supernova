#include <headers/Player.h>
#include <SFML/Graphics.hpp>
#include <iostream>

float playerJumpSpeed, playerSpeed, playerSize, animationPerFrame = 1.0f / 8.0f;
int frameCount = 0, offset = 0;
const float gravity = 1.f;
sf::Sprite playerSprite;
sf::Texture texture;
sf::Vector2f velocity(sf::Vector2f(0, 0));
bool grounded = true;
float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

void Player::init() {
	
	//this is how fast we want the player. If we want to change their speed this can be changed.
	playerSpeed = 6.0f;
	playerJumpSpeed = 6.0f;
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
void Player::checkMovement(std::vector<Vector2> vectors, LevelManager::Level currentLevel) {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		if (checkCollision(playerSpeed, vectors, currentLevel)) {
			x += playerSpeed;
			velocity.x = playerSpeed;
			//the sprite size in sprite sheet is 800x1600. this tells textureRect to start at beginning and every time walkCount is added, then it goes to next frame
			playerSprite.setTextureRect(sf::IntRect(offset * 834, 0, 834, 1668));
		}
		else { velocity.x = 0; }
		
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if(checkCollision(-playerSpeed, vectors, currentLevel)){
			x -= playerSpeed;
			velocity.x = -playerSpeed;
			//the left facing frames are at 800*2 x 1600 so this tells does same as above but lower on the sprite sheet
			playerSprite.setTextureRect(sf::IntRect(offset * 834, 834 * 2, 800, 1668));
		}
		else { velocity.x = 0; }

	}
	else{
		velocity.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y = -playerJumpSpeed;
	}
	if (!grounded||velocity.y<0) {
		velocity.y += gravity;
	}
	else {
		velocity.y = 0;
	}
	if(checkCollision(-playerSpeed, vectors, currentLevel)|| checkCollision(playerSpeed, vectors, currentLevel))
	playerSprite.move(velocity.x, velocity.y);

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
	x = startPosition.x * 64;
	y = startPosition.y * 64;
}

void Player::update(std::vector<Vector2> vectors, LevelManager::Level currentLevel) {
	//checkCollision(playerSpeed, vectors, currentLevel);
	checkMovement(vectors, currentLevel);
}

//returns false if movement will cause collision. returns true otherwise
bool Player::checkCollision(float velo, std::vector<Vector2> vectors, LevelManager::Level currentLevel) {

	float bot = ceil(playerSprite.getGlobalBounds().top + 128);
	float top = ceil(playerSprite.getGlobalBounds().top);
	float left = ceil(playerSprite.getGlobalBounds().left);
	float mid = ceil(playerSprite.getGlobalBounds().left + 32);
	float right = ceil(playerSprite.getGlobalBounds().left + 64);


	sf::Vector2f topLeft(left, top);
	sf::Vector2f topRight(right, top);
	sf::Vector2f botLeft(left, bot);
	sf::Vector2f botLeftHigh(left+velo, bot-32);
	sf::Vector2f botRight(right, bot);
	sf::Vector2f botRightHigh(right+velo, bot-32);

	//std::cout << "topLeft Cell: " << floor(topLeft.x / 64) << " topLeft Cell:" << floor(topLeft.y / 64) << std::endl;
	//std::cout << "topRight Cell: " << floor(topRight.x / 64) << " topRight Cell:" << floor(topRight.y / 64) << std::endl;
	//std::cout << "botLeft Cell: " << floor(botLeft.x / 64) << " botLeft Cell:" << floor(botLeft.y / 64) << std::endl;
	//std::cout << "botRight Cell: " << floor(botRight.x / 64) << " botRight Cell:" << floor(botRight.y / 64) << std::endl;
	std::cout << "botRightHigh Cell: " << floor(botRightHigh.x / 64) << " botRight Cell:" << (floor(botRightHigh.x / 64) < currentLevel.width) << std::endl;
	float nx = x + velo;
	float ny = y;
	//std::cout << "Future position " << nx << "\n";
	if (botRightHigh.x > (currentLevel.width * 64) || botLeftHigh.x <0 ) {
		return false;
	}
	if (floor(botLeftHigh.x / 64) >= 0 || floor(botRightHigh.x / 64) < currentLevel.width ) {
		if (currentLevel.colMap.at(floor(botRight.y / 64)).at(floor(botRight.x / 64)) == 1
			|| currentLevel.colMap.at(floor(botLeft.y / 64)).at(floor(botLeft.x / 64)) == 1) {
			grounded = true;

		}
		else {
			grounded = false;
		}
		if (currentLevel.colMap.at(floor(botRightHigh.y / 64)).at(floor(botRightHigh.x / 64)) == 1 || currentLevel.colMap.at(floor(botLeftHigh.y / 64)).at(floor(botLeftHigh.x / 64)) == 1) {
			return false;
		}
	}
	//std::cout << "Current Position " << playerSprite.getPosition().x << " " << playerSprite.getPosition().y << "\n";
	if (nx > (currentLevel.width + 3) * 64 || nx < 256) {
		return false;
	}
	if (velo > 0) {//moving right
		for (auto& vec : vectors) {
			if (vec.x < x) {
				continue;
			}
			if ((vec.x == nx || vec.x <= nx + 64) && (vec.y == ny || ny - 64 == vec.y)) {
				return false;
			}
		}
	}
	else {//moving left
		for (auto& vec : vectors) {
			if (vec.x > x) {
				continue;
			}
			if ((vec.x == nx || vec.x >= nx - 64) && (vec.y == y || ny - 64 == vec.y)) {
				return false;
			}
		}
	}

	return true;
}