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

void Player::draw() {

	/*sf::Texture texture;
	if (!texture.loadFromFile("img/astronaut.png")) {
		std::cout << "Could not load astronaut texture" << std::endl;
		return;
	}
	sf::Sprite playerSprite;
	playerSprite.setTexture(texture);*/

	glBegin(GL_QUADS);
		glVertex2f(-0.5f, 0.5f); // top left
		glVertex2f(0.5f, 0.5f); // top right 
		glVertex2f(0.5f, -0.5f); // bottom right
		glVertex2f(-0.5f, -0.5f); // bottom left
	glEnd();
}