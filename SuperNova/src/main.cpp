#include <GL/glut.h>
#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <iostream>

#include "../src/obj/Player.h"

void draw();
void update();

Player player;

// creates global window
sf::RenderWindow window(sf::VideoMode(800, 600), "SuperNova");

int main(int argc, char **argv)
{
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

		//update();
		draw();

	}

	return 0;
}

void draw() {
	window.clear();

	// draw objects here
	player.draw(window);

	window.display();
}

void update() {
	player.update();
}