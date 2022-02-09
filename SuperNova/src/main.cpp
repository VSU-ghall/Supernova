#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <iostream>
#include "../src/objects/Player.h"
#include "../src/objects/TileMap.h"
#include "GameEngine.h"

int main(int argc, char** argv) {
	GameEngine game;
	game.run();

	return 0;
}
