#pragma once
#include "Vector2.h"
#include "iostream"

static class LevelManager
{
	public:
		struct Level {
			int* map;
			Vector2 startPosition;
		};

		LevelManager();
		Level getTestLevel();
		Level getLevel1();
		Level getLevel2();

	private:
		static const int levelSize = 240;
		Level testLevel, level1, level2;
		void init();
};

