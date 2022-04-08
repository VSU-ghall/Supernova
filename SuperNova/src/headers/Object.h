#pragma once
#include <stdlib.h>
#include <headers/Sprite.h>

class Object
{
	public:
		Object();
		Object(int index, int iconIndex, Sprite* sprite);

		Sprite* getObject();
		Sprite* getIcon();
		int getIconIndex();
		int getIndex();
		sf::Vector2i getSize();
		bool isHidden();
		bool hasHiddenIcon();
		bool hasIcon();

		void activateIcon();
		void collect();
		void deactivateIcon();
		void hide();
		void hideIcon();
		void setIcon(bool boolIcon);
		void show();


	private:
		Sprite* sprite, *icon;
		int index, iconIndex;
		bool hidden = false, hiddenIcon = true, active = false, boolIcon = false;
};

