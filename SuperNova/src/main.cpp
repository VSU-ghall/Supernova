<<<<<<< HEAD
#include <GL/glut.h>
#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <iostream>
#include "../src/obj/Player.h"

void draw();
void update();
void drawGrid();

Player player;
//changes
// creates global window
sf::RenderWindow window(sf::VideoMode(20*128, 12*128), "SuperNova", sf::Style::Fullscreen);

int main(int argc, char **argv)
{
	player.init();
	// main loop --> continues each frame while window is open
	while (window.isOpen()) {

		// event handling
		sf::Event event;
		while (window.pollEvent(event)) {

			// event triggered when window is closed
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		update();
		draw();

	}

	return 0;
}

//
// Draws all objects on window
//
void draw() {
	window.clear();

	// draw objects here
	player.draw(window);
	drawGrid();

	window.display();
}

//
// Updates all game objects
//
void update() {
	player.update();
	player.checkMovment();
}

void drawGrid() {
	for (int x = 0; x < window.getSize().x; x = x+128) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(x, 0);
		lines[0].color = sf::Color::White;
		lines[1].position = sf::Vector2f(x, window.getSize().y);
		lines[1].color = sf::Color::White;

		window.draw(lines);
	}

	for (int y = 0; y < window.getSize().y; y = y + 128) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(0, y);
		lines[0].color = sf::Color::White;
		lines[1].position = sf::Vector2f(window.getSize().x, y);
		lines[1].color = sf::Color::White;

		window.draw(lines);
	}
=======
#include "GameEngine.h"

int main(int argc, char** argv) {
	GameEngine game;
	game.run();

	return 0;
>>>>>>> db3e313d0918083fdbd5ce186a7397541b574211
}