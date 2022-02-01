#include "Player.h"
#include <GL/glut.h>

float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

void Player::update() {

}

void Player::draw() {
	glBegin(GL_QUADS);
		glVertex2f(-0.5f, 0.5f); // top left
		glVertex2f(0.5f, 0.5f); // top right 
		glVertex2f(0.5f, -0.5f); // bottom right
		glVertex2f(-0.5f, -0.5f); // bottom left
	glEnd();
}