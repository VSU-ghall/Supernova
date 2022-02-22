#include <headers/Player.h>
#include <SFML/Graphics.hpp>
#include <iostream>

float playerJumpSpeed, playerSpeed, playerSize, animationPerFrame = 1.0f / 8.0f;
int frameCount = 0, offset = 0;
const float gravity = 1.f;
sf::Sprite playerSprite;
sf::Texture texture;
sf::Vector2f velocity(0,0);
bool grounded = true;
bool jumping = false;
bool ceilingBump = false;
int jumpFrames = 0;
float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

void Player::init() {
	
	//this is how fast we want the player. If we want to change their speed this can be changed.
	playerSpeed = 6.0f;
	playerJumpSpeed = 9.0f;
	//playerSprite.setPosition(64 * 5, 64 * 9);
	playerSprite.setPosition(64 * startPosition.x, 64 * startPosition.y);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 834, 1666));
	x = startPosition.x * 64;
	y = startPosition.y * 64;
	
	//this is the Size of the player
	playerSize = 64/834.f;

	//setting the initial size of the player.
	playerSprite.setScale(playerSize, playerSize);
	
	if (!texture.loadFromFile("src/resources/astronaut_walk.png")) {
		std::cout << "Could not load astronaut texture" << std::endl;
	}
	playerSprite.setTexture(texture);

	//the set Origin will put a "point" in the middle of the sprite and the sprite will now rotate around that point when manipulated.
	playerSprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
}

void Player::animate() {
	if (stoppedRight && !moving)
		playerSprite.setTextureRect(sf::IntRect(0, 0, 800, 1668));
	else if (stoppedLeft && !moving)
		playerSprite.setTextureRect(sf::IntRect(0, 834 * 2, 800, 1668));

	frameCount++;
	if ((int)(frameCount * animationPerFrame) > offset) offset++;

	//There are 8 frames for walking now, this allows each frame to cycle and then reset when the last frame is projected onto the screen
	if (offset == 8) {
		frameCount = 0;
		offset = 0;
	}
}

// 
// Checks if A or D is pressed and moves left or right respectively
// ( Movement is animated on a ratio (set by the variable animationPerFrame) )
//
void Player::checkMovement(std::vector<Vector2> vectors, LevelManager::Level currentLevel) {
	animate();

	if (grounded && 
		!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && 
		!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		return;

	bool checkLeft = checkCollision(-playerSpeed, vectors, currentLevel),
		checkRight = checkCollision(playerSpeed, vectors, currentLevel);

	if (checkRight && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		stoppedLeft = false; stoppedRight = true;
		moving = true;

		velocity.x = playerSpeed;
		//the sprite size in sprite sheet is 800x1600. this tells textureRect to start at beginning and every time walkCount is added, then it goes to next frame
		playerSprite.setTextureRect(sf::IntRect(offset * 834, 0, 834, 1668));
		
	}
	else if (checkLeft && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		stoppedLeft = true;  stoppedRight = false;
		moving = true;

		velocity.x = -playerSpeed;
		//the left facing frames are at 800*2 x 1600 so this tells does same as above but lower on the sprite sheet
		playerSprite.setTextureRect(sf::IntRect(offset * 834, 834 * 2, 800, 1668));
	}
	else{
		velocity.x = 0;
	}

	if (!jumping) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && grounded) {
			velocity.y = -playerJumpSpeed;
			jumping = true;
			jumpFrames = 0;
		}
		else if (!grounded || velocity.y < 0) {
			velocity.y = velocity.y * .9f + gravity;
		}
		else {
			velocity.y = 0;
		}
	}
	else {
		if (ceilingBump) {
			velocity.y = 0;
			ceilingBump = false;
			jumping = false;
		}
		else if (jumpFrames < 15) {
			velocity.y = -playerJumpSpeed;
			jumpFrames++;
		}
		else {
			jumping = false;
			jumpFrames = 0;
		}
	}

	x += velocity.x;
	y += velocity.y;
	playerSprite.move(velocity.x, velocity.y);
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

	sf::Vector2f topLeftHigh(left + velo, top + 32);
	sf::Vector2f botLeftHigh(left + velo, bot-32);
	sf::Vector2f botLeft(left + velo, bot);

	sf::Vector2f topRightHigh(right + velo, top + 32);
	sf::Vector2f botRightHigh(right+velo, bot-32);
	sf::Vector2f botRight(right + velo, bot);

	//If out of level bounds
	if (left + velo <= 0 || right+velo >= (currentLevel.width * 64)) return false;
	
	checkTopBotCollision(topRight, botRight, topLeft, botLeft, currentLevel);

	return checkSideCollision(botRightHigh, botLeftHigh, topRightHigh, topLeftHigh, currentLevel);
}

bool Player::checkSideCollision(sf::Vector2f botRightHigh, sf::Vector2f botLeftHigh, sf::Vector2f topRightHigh, sf::Vector2f topLeftHigh, LevelManager::Level currentLevel) {

	bool blockTopLeftHigh = currentLevel.colMap.at(floor(topLeftHigh.y / 64)).at(floor(topLeftHigh.x / 64)) == 1,
		blockBotLeftHigh = currentLevel.colMap.at(floor(botLeftHigh.y / 64)).at(floor(botLeftHigh.x / 64)) == 1,
		blockTopRightHigh = currentLevel.colMap.at(floor(topRightHigh.y / 64)).at(floor(topRightHigh.x / 64)) == 1,
		blockBotRightHigh = currentLevel.colMap.at(floor(botRightHigh.y / 64)).at(floor(botRightHigh.x / 64)) == 1;

	if (blockTopLeftHigh || blockBotLeftHigh || blockTopRightHigh || blockBotRightHigh)
		return false;

	return true;
}

void Player::checkTopBotCollision(sf::Vector2f topRight, sf::Vector2f botRight, sf::Vector2f topLeft, sf::Vector2f botLeft, LevelManager::Level currentLevel) {
	
	bool blockTopLeft = currentLevel.colMap.at(floor(topLeft.y / 64)).at(floor(topLeft.x / 64)) == 1,
		blockBottomLeft = currentLevel.colMap.at(floor(botLeft.y / 64)).at(floor(botLeft.x / 64)) == 1,
		blockTopRight = currentLevel.colMap.at(floor(topRight.y / 64)).at(floor(topRight.x / 64)) == 1,
		blockBottomRight = currentLevel.colMap.at(floor(botRight.y / 64)).at(floor(botRight.x / 64)) == 1;

	if (blockBottomRight || blockBottomLeft) grounded = true;
	else grounded = false;

	if (blockTopRight || blockTopLeft) ceilingBump = true;
	else ceilingBump = false;
}