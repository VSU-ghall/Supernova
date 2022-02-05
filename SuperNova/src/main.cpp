#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <iostream>
#include "../src/obj/Player.h"
#include "../src/obj/TileMap.h"

void init();
void draw();
void update();
void drawGrid();

Player player;
TileMap map;
const int tileSize = 64, levelWidth = 20, levelHeight = 12;

// creates global window
sf::RenderWindow window(sf::VideoMode(levelWidth * tileSize, levelHeight * tileSize), "SuperNova");

int main(int argc, char **argv)
{
	// define the level with an array of tile indices
	const int level[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	};

	// create the tilemap from the level definition
	
	if (!map.load("src/img/testTileSet.png", sf::Vector2u(64,64), level, levelWidth, levelHeight))
		return -1;

	init();
	int frames = 0;

	// main loop --> continues each frame while window is open
	while (window.isOpen()) {

		// event handling
		sf::Event event;
		while (window.pollEvent(event)) {

			// event triggered when window is closed
			if (event.type == sf::Event::Closed || event.type == sf::Keyboard::Escape) {
				window.close();
			}

		}

		update();
		draw();

		frames++;
		std::cout << frames<< std::endl;
	}

	return 0;
}

//
//	Initializes the game components
//
void init() {
	window.setFramerateLimit(60);
	player.init();
}

//
// Draws all objects on window
//
void draw() {
	window.clear();
	
	window.draw(map);

	drawGrid();

	player.draw(window);

	window.display();
}

//
// Updates all game objects
//
void update() {
	player.update();
}

void drawGrid() {
	for (int x = 0; x <= window.getSize().x; x = x + tileSize) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(x, 0);
		lines[0].color = sf::Color::White;
		lines[1].position = sf::Vector2f(x, window.getSize().y);
		lines[1].color = sf::Color::White;

		window.draw(lines);
	}

	for (int y = 0; y <= window.getSize().y; y = y + tileSize) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(0, y);
		lines[0].color = sf::Color::White;
		lines[1].position = sf::Vector2f(window.getSize().x, y);
		lines[1].color = sf::Color::White;

		window.draw(lines);
	}
}