#pragma once
#include "headers/GameEngine.h"
#include "iostream"

class StoryManager
{
public:
	StoryManager(GameEngine* game) {
		this->game = game;
		this->levelManager = game->getLevelManager();
		this->player = game->getPlayer();
	}

	static void startIntroduction();

private:
	GameEngine* game = NULL;
	LevelManager* levelManager = NULL;
	Player* player = NULL;

};

