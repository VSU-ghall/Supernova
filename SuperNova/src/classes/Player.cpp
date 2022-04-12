#include <headers/Player.h>
#include <SFML/Graphics.hpp>
#include <iostream>

float playerJumpSpeed, playerSpeed, playerSize, animationPerFrame = 1.0f / 8.0f, jumpHeight = 0;
int offset = 0, offsetJetPack = 0;
float gravity = 1.f;
sf::Vector2f velocity(0, 0);
bool grounded = true, jumping = false, ceilingBump = false, crouchPlayed = false;
bool readyToTransition = false;

float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

int Player::getJetPackFuel()
{
	return jetpackFuel;
}

float Player::getHp() {
	return hp;
}

sf::FloatRect Player::getBoundingBox() {
	return playerSprite.getGlobalBounds();
}

void Player::init(bool* displayingText) {

	this->displayingText = displayingText;

	//this is how fast we want the player. If we want to change their speed this can be changed.
	playerSpeed = 6.0f;
	playerJumpSpeed = 9.0f;
	playerSprite.setPosition(tileSize * startPosition.x, tileSize * startPosition.y);
	playerSprite.setTextureRect(frameStoppedLeft);
	x = startPosition.x * tileSize;
	y = startPosition.y * tileSize;

	dashBoots = false;
	dashCooldown = DASH_COOLDOWN;
	
	jetPack = false;
	jetpackFuel = JETPACK_MAXIMUM;
	//this is the Size of the player
	//playerSize = 64/834.f;
	playerSize = 2.f;

	//setting the initial size of the player.
	playerSprite.setScale(playerSize, playerSize);

	if (!texture.loadFromFile("src/resources/astronaut_walk.png")) {
		std::cout << "Could not load astronaut texture" << std::endl;
	}
	playerSprite.setTexture(texture);

	// Set global bounds rectangle data for troubleshooting
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(2.0f);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
}

void Player::animate() {
	if (stoppedRight && !moving) {
		if (jetPack && !grounded) playerSprite.setTextureRect(frameJetpackRight);
		else playerSprite.setTextureRect(frameStoppedRight);
	}
	else if (stoppedLeft && !moving) {
		if (jetPack && !grounded) playerSprite.setTextureRect(frameJetpackLeft);
		else playerSprite.setTextureRect(frameStoppedLeft);
	}

	if (walkTimer.getElapsedTime().asMilliseconds() >= 150 * offset) offset++;
	if (jetTimer.getElapsedTime().asMilliseconds() >= 150 * offsetJetPack) offsetJetPack++;


	//There are 8 frames for walking now, this allows each frame to cycle and then reset when the last frame is projected onto the screen
	if (offset == 8 || (!moving && grounded)) {
		walkTimer.restart();
		offset = 0;
	}

	if (offsetJetPack == 3 || grounded) {
		jetTimer.restart();
		offsetJetPack = 0;
	}
}

// 
// Checks if A or D is pressed and moves left or right respectively
// ( Movement is animated on a ratio (set by the variable animationPerFrame) )
//
void Player::checkMovement(LevelManager::Level currentLevel) {


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		crouchPlayed = false;
	if (grounded && jetpackFuel < JETPACK_MAXIMUM) {
		jetpackFuel++;
	}
	if (dashCooldown < DASH_COOLDOWN) {
		dashCooldown++;
	}
	if (grounded && !dashing &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		return;

	bool checkLeft = checkCollision(-playerSpeed, currentLevel),
		checkRight = checkCollision(playerSpeed, currentLevel);


	if (checkRight && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		stoppedLeft = false; stoppedRight = true;
		moving = true;

		velocity.x = playerSpeed;
		//the sprite size in sprite sheet is 32x64. this tells textureRect to start at beginning and every time walkCount is added, then it goes to next frame
		playerSprite.setTextureRect(sf::IntRect(offset * 32, 0, 32, 64));
	}
	else if (checkLeft && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		stoppedLeft = true;  stoppedRight = false;
		moving = true;

		velocity.x = -playerSpeed;
		//the left facing frames are at 32*2 x 64 so this tells does same as above but lower on the sprite sheet
		playerSprite.setTextureRect(sf::IntRect(offset * 32, 32 * 2, 32, 64));
	}
	else {
		velocity.x = 0;
	}

	if (dashBoots && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& dashCooldown==DASH_COOLDOWN) {
		dashing = true;
		dashDistance = 0;
		dashCooldown = 0;
		gravity = 0;
	}
	if (dashing && dashDistance < DASH_TOTAL_DISTANCE && checkCollision(DASH_SPEED, currentLevel) && stoppedRight) {
		velocity.x = DASH_SPEED;
		velocity.y = 0;
		dashDistance += DASH_SPEED;

	}
	else if (dashing && dashDistance > -DASH_TOTAL_DISTANCE && checkCollision(-DASH_SPEED, currentLevel) && stoppedLeft) {
		velocity.x = -DASH_SPEED;
		velocity.y = 1;
		dashDistance -= DASH_SPEED;

	}
	else {
		dashing = false;
		gravity = 1.f;
	}
	if (jetPack) {

		if (checkCollision(0, currentLevel))
			
			if (!ceilingBump) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&& jetpackFuel>0) {
					velocity.y = -playerJumpSpeed;
					jetpackFuel--;
				}

				if (!grounded || velocity.y < 0) {
					velocity.y = velocity.y * .9f + gravity;
				}
				else {
					velocity.y = 0;
					
				}
			}
			else{
				velocity.y = 1;
				ceilingBump = false;
				jumping = false;
				if (jetpackFuel > 0)
				jetpackFuel--;
			}
	}
	else {
		if (!jumping && !ceilingBump) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && grounded) {
				velocity.y = -playerJumpSpeed;
				jumping = true;
				jumpHeight = 0;
				playJumpSound();
			}
			else if (!grounded || velocity.y < 0) {
				//if player is suspended in air, then the jumping animation is set depending on direction astronaut is facing
				velocity.y = velocity.y * .95f + gravity;
			}
			else {
				//if s key is pressed, the astronaut crouches and cannot move along the x-axis 
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && stoppedRight) {
					playerSprite.setTextureRect(frameSquatRight);
					velocity.x = 0;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && stoppedLeft) {
					playerSprite.setTextureRect(frameSquatLeft);
					velocity.x = 0;
				}

				playCrouchSound();
				velocity.y = 0;
			}
		}
		else {
			if (ceilingBump) {
				velocity.y = 1;
				ceilingBump = false;
				jumping = false;
			}
			else if (jumpHeight < 100) {
				velocity.y = -playerJumpSpeed;
				jumpHeight -= velocity.y;
			}
			else {
				jumping = false;
				jumpHeight = 0;
			}
		}
	}
	if (!jetPack && (!grounded || jumping)) {
		if (stoppedRight) {
			playerSprite.setTextureRect(frameJumpRight);
		}
		else if (stoppedLeft) {
			playerSprite.setTextureRect(frameJumpLeft);
		}
	}
	else if (jetPack && !grounded) {
		if (stoppedRight) {
			playerSprite.setTextureRect(sf::IntRect(offsetJetPack * 38, 322, 38, 64));
		}
		else if (stoppedLeft) {
			playerSprite.setTextureRect(sf::IntRect((offsetJetPack * 38)+114, 322, 38, 64));
		}
	}

	// sets player's position to always be on top of a block (not a few pixels inside of it)
	sf::Vector2f pos = playerSprite.getPosition();
	if (grounded && !jumping && (int)(pos.y+128) % 64 != 0) {

		pos.y = (int)((pos.y + 10) / 64) * 64;

		playerSprite.setPosition(pos);
	}

	x += velocity.x;
	y += velocity.y;
	playerSprite.move(velocity.x, velocity.y);
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(playerSprite);

	// Set global bounds rectangle data for troubleshooting
	/*sf::FloatRect bounds = playerSprite.getGlobalBounds();
	rect.setSize(sf::Vector2f(bounds.width, bounds.height));

	rect.setPosition(playerSprite.getPosition());
	window.draw(rect);*/
}

void Player::die() {
	dead = true;

	// Animate death here
}

void Player::respawn() {
	playerSprite.setPosition(tileSize * startPosition.x, tileSize * startPosition.y);
	x = startPosition.x * tileSize;
	y = startPosition.y * tileSize;
}

void Player::update(LevelManager::Level currentLevel) {
	if (!takingDamage) {
		animate();
		checkMovement(currentLevel);
	}
	checkItems(currentLevel);

	if (damageTimer.getElapsedTime().asSeconds() >= 0.1) takingDamage = false;
}

void Player::checkItems(LevelManager::Level currentLevel) {
	for (auto obj : currentLevel.objects) {
		if (!obj->isHidden() && playerSprite.getGlobalBounds().intersects(obj->getObject()->getSprite()->getGlobalBounds())) {
			if (obj->hasIcon()) obj->collect();
		}
	}
}

//returns false if movement will cause collision. returns true otherwise
bool Player::checkCollision(float velo, LevelManager::Level currentLevel) {

	float bot = ceil(playerSprite.getGlobalBounds().top + 128);
	float top = ceil(playerSprite.getGlobalBounds().top);
	float left = ceil(playerSprite.getGlobalBounds().left);
	float mid = ceil(playerSprite.getGlobalBounds().left + 32);
	float right = ceil(playerSprite.getGlobalBounds().left + 64);

	sf::Vector2f topLeft(left, top);
	sf::Vector2f topRight(right, top);

	sf::Vector2f topLeftHigh(left + (-std::abs(velo)), top + 32);
	sf::Vector2f botLeftHigh(left + (-std::abs(velo)), bot - 32);
	sf::Vector2f botLeft(left + (-std::abs(velo)), bot);

	sf::Vector2f botMidLeft(left + 5, bot);
	sf::Vector2f botMid(mid, bot);
	sf::Vector2f botMidRight(right - 5, bot);

	sf::Vector2f topRightHigh(right + velo, top + 32);
	sf::Vector2f botRightHigh(right + velo, bot - 32);
	sf::Vector2f botRight(right + velo, bot);

	//If out of level bounds

	//if (left + velo <= 6 || right + velo >= (currentLevel.width * tileSize) - 6) return false;
	checkTopBotCollision(topRight, botRightHigh, botRight, botMidRight, botMid, botMidLeft, topLeft, botLeftHigh, botLeft, currentLevel);
	return checkTransitionCollision(left, right, top, bot, velo, botRightHigh, botLeftHigh, topRightHigh, topLeftHigh, currentLevel);
}

//Note: The values of collisionTile and transitionTile can be changed in TileMap.h

bool Player::checkSideCollision(float velo, sf::Vector2f botRightHigh, sf::Vector2f botLeftHigh, sf::Vector2f topRightHigh, sf::Vector2f topLeftHigh, LevelManager::Level currentLevel) {
	bool blockTopLeftHigh = checkTile(currentLevel, topLeftHigh, currentLevel.collisionTile), blockBotLeftHigh = checkTile(currentLevel, botLeftHigh, currentLevel.collisionTile),
		blockTopRightHigh = checkTile(currentLevel, topRightHigh, currentLevel.collisionTile), blockBotRightHigh = checkTile(currentLevel, botRightHigh, currentLevel.collisionTile);

	if (((blockTopLeftHigh || blockBotLeftHigh) && velo < 0) || ((blockTopRightHigh || blockBotRightHigh)) && velo > 0) {		
		if (drilling) {
			if (checkTile(currentLevel, botLeftHigh, 4)) {
				int i = floor(botLeftHigh.y / tileSize) * currentLevel.width + floor(botLeftHigh.x / tileSize);

				currentLevel.map[i - currentLevel.width] = 0;
				currentLevel.map[i] = 0;

				currentLevel.levelManager->setLevel(currentLevel);

			}
			else if (checkTile(currentLevel, botRightHigh, 4)) {
				int i = floor(botRightHigh.y / tileSize) * currentLevel.width + floor(botRightHigh.x / tileSize);

				currentLevel.map[i - currentLevel.width] = 0;
				currentLevel.map[i] = 0;

				currentLevel.levelManager->setLevel(currentLevel);
			}
		}

		return false;
	}

	return true;
}

/*void Player::checkTransitionCollision(sf::Vector2f topRight, sf::Vector2f botRight, sf::Vector2f topLeft, sf::Vector2f botLeft, LevelManager::Level currentLevel) {
	bool blockTopLeftHigh = checkTile(currentLevel, topRight, currentLevel.transitionTile), blockBotLeftHigh = checkTile(currentLevel, botRight, currentLevel.transitionTile),
		blockTopRightHigh = checkTile(currentLevel, topLeft, currentLevel.transitionTile), blockBotRightHigh = checkTile(currentLevel, botLeft, currentLevel.transitionTile);
	if (blockBotRightHigh || blockTopRightHigh || blockBotLeftHigh || blockTopLeftHigh) {
		readyToTransition = true;*/

bool Player::checkTransitionCollision(float left, float right, float top, float bot, float velo, sf::Vector2f botRightHigh, sf::Vector2f botLeftHigh, sf::Vector2f topRightHigh, sf::Vector2f topLeftHigh, LevelManager::Level currentLevel) {
	bool checkLeftEdge = left + velo <= 16;
	bool checkRightEdge = right + velo >= (currentLevel.width * 64) - 16;
	bool checkBotEdge = bot + velo >= (currentLevel.height * 64) - 12;
	bool checkTopEdge = top - velo <= 63;
	//std::cout << top - velo << std::endl;

	if (checkLeftEdge || checkRightEdge || checkBotEdge || checkTopEdge) {
		if (!*displayingText) {
			if (checkLeftEdge) transitioningLeft = true;
			if (checkRightEdge) transitioningRight = true;
			if (checkBotEdge) transitioningBot = true;
			if (checkTopEdge) transitioningTop = true;

			grounded = true;
			velocity.y = 0;
		}

		return false;
	}
	else return checkSideCollision(velo, botRightHigh, botLeftHigh, topRightHigh, topLeftHigh, currentLevel);
}

void Player::checkTopBotCollision(sf::Vector2f topRight, sf::Vector2f botRightHigh, sf::Vector2f botRight, sf::Vector2f botMidRight, sf::Vector2f botMid, sf::Vector2f botMidLeft, sf::Vector2f topLeft, sf::Vector2f botLeftHigh, sf::Vector2f botLeft, LevelManager::Level currentLevel) {

	bool blockTopLeft = checkTile(currentLevel, topLeft, currentLevel.collisionTile), blockBotLeftHigh = checkTile(currentLevel, botLeftHigh, currentLevel.collisionTile), blockBottomLeft = checkTile(currentLevel, botLeft, currentLevel.collisionTile),
		blockBotMidLeft = checkTile(currentLevel, botMidLeft, currentLevel.collisionTile), blockBotMid = checkTile(currentLevel, botMid, currentLevel.collisionTile), blockBotMidRight = checkTile(currentLevel, botMidRight, currentLevel.collisionTile),
		blockTopRight = checkTile(currentLevel, topRight, currentLevel.collisionTile), blockBotRightHigh = checkTile(currentLevel, botRightHigh, currentLevel.collisionTile), blockBottomRight = checkTile(currentLevel, botRight, currentLevel.collisionTile);

	if ((blockBottomLeft && !blockBotMidLeft) || (blockBottomRight && !blockBotMidRight)) {
		grounded = false;
	}
	else if ((blockBottomLeft && !blockBotLeftHigh) || (blockBottomRight && !blockBotRightHigh) || blockBotMid) {
		grounded = true;
	}
	else {
		grounded = false;
	}

	if (blockTopRight || blockTopLeft) {
		ceilingBump = true;
	}
	else {
		ceilingBump = false;
	}
}

void Player::DrillCollision(float velo, LevelManager::Level currentLevel) {

	float bot = ceil(playerSprite.getGlobalBounds().top + 128);
	float top = ceil(playerSprite.getGlobalBounds().top);
	float left = ceil(playerSprite.getGlobalBounds().left);
	float mid = ceil(playerSprite.getGlobalBounds().left + 32);
	float right = ceil(playerSprite.getGlobalBounds().left + 64);



	sf::Vector2f botLeftHigh(left + (-std::abs(velo)), bot - 32);
	sf::Vector2f botRightHigh(right + velo, bot - 32);


	if (checkTile(currentLevel, botLeftHigh, 4)) {
		int i = floor(botLeftHigh.y / tileSize) * currentLevel.width + floor(botLeftHigh.x / tileSize);
		
		currentLevel.map[i- currentLevel.width] = 0;
		currentLevel.map[i] = 0;

	}
	else if (checkTile(currentLevel, botRightHigh, 4)) {
		int i = floor(botRightHigh.y / tileSize) * currentLevel.width + floor(botRightHigh.x / tileSize);

		currentLevel.map[i - currentLevel.width] = 0;
		currentLevel.map[i] = 0;
	}

}

bool Player::checkTile(LevelManager::Level currentLevel, sf::Vector2f position, int remainder) {
	return currentLevel.colMap.at(floor(position.y / tileSize)).at(floor(position.x / tileSize)) >= remainder;
}

void Player::playCrouchSound()
{
	//sound for crouch
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && music.getStatus() == sf::SoundSource::Stopped && !crouchPlayed)
	{
		if (!music.openFromFile("src/resources/sounds/astronaut_crouch.wav"))
		{
			std::cout << "Could not load astronaut crouch sound" << std::endl;
			return;
		}

		music.setVolume(5);

		music.play();
		crouchPlayed = true;
	}
}

void Player::playJumpSound() {
	//sound for jump
	if (!music.openFromFile("src/resources/sounds/astronaut_jump.wav"))
	{
		std::cout << "Could not load astronaut jump sound" << std::endl;
		return;
	}

	music.setVolume(5);

	music.play();
}

void Player::playWalkSound()
{
	//sound for jump
	if (music.getStatus() == sf::SoundSource::Stopped) {
		if (!music.openFromFile("src/resources/sounds/astronaut_walking.wav"))
		{
			std::cout << "Could not load astronaut walk sound" << std::endl;
			return;
		}
		music.setVolume(100);

		music.play();
	}
}

float Player::takeDamage(float damage) {
	takingDamage = true; damageTimer.restart();
	hp -= damage;

	playerSprite.setTextureRect(frameDamaged);

	if (hp <= 0) {
		hp = 0;

		die();
	}
	return hp;
}

