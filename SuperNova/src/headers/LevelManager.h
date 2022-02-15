#pragma once


static class LevelManager
{
	private:
		static const int levelSize = 240;
		int* testLevel;
		int* level1;
		int* level2;
		void init();

	public:
		LevelManager();
		int* getTestLevel();
		int* getLevel1();
		int* getLevel2();
};

