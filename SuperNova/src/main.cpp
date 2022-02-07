#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <iostream>
#include "../src/obj/Player.h"
#include "../src/obj/TileMap.h"
#include "../examples/sound/Sound.h"

void init();
void draw();
void update();
void drawGrid();
sf::View getViewport(float width, float height);

Player player;
TileMap map;
const int tileSize = 64;
int levelWidth = 20, levelHeight = 12;
float windowWidth = tileSize * levelWidth, windowHeight = tileSize * levelHeight;

// creates global window
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SuperNova");
sf::View view;

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

	// main loop --> continues each frame while window is open
	while (window.isOpen()) {

		// event handling
		sf::Event event;
		while (window.pollEvent(event)) {

			// event triggered when window is closed
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}

			// sets viewport when window is resized
			if (event.type == sf::Event::Resized)
				view = getViewport(event.size.width, event.size.height);

		}

		update();
		draw();
	}

	return 0;
}

//
//	Initializes the game components
//
void init() {
	view.setSize(windowWidth, windowHeight);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	view = getViewport(windowWidth, windowHeight);

	window.setFramerateLimit(60);
	player.init();
}

//
// Draws all objects on window
//
void draw() {
	window.clear();
	
	window.setView(view);
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

//
// Draws grid for development/testing purposes
//
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

//
// Sets viewport to keep game aspect ratio
// ** Adapted from official SFML wiki (src: https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view)
//
sf::View getViewport(float width, float height) {
	float windowRatio = width / height;
	float viewRatio = windowWidth / windowHeight;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	// If horizontalSpacing is true, the black bars will appear on the left and right side.
	// Otherwise, the black bars will appear on the top and bottom.

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}
	else {
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

	return view;
}