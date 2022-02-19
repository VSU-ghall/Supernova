#pragma once
#include "Vector2.h"


class Component {

};

class CMovement : public Component {
public:
	Vector2 position = { 0.0, 0.0 };
	Vector2 velocity = { 0.0, 0.0 };

	CMovement() {}
	CMovement(Vector2 & pos, Vector2 & velo)
		:position(pos), velocity(velo) {}

};