#include "headers/GameEngine.h"
#include "headers/StoryManager.h"
#include <SFML/System.hpp>

int main(int argc, char** argv) {
	GameEngine game;
	StoryManager storyManager(&game);

	//sf::Thread gameLoop(&runGame, &game);
	//gameLoop.launch();

	game.run();

	return 0;
}