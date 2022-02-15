#pragma once

/*
	Resource used for vector math: https://medium.com/linear-algebra-basics/vector-basic-operations-5f084ecee391.
	Resource for operator overloading: https://www.geeksforgeeks.org/operator-overloading-c/.
*/
class Vector2
{

public:

	float x = 0;
	float y = 0;

	Vector2(); //Constructs vector with x and y equal to zero
	Vector2(float x, float y);

	Vector2 operator + (Vector2 v);
	Vector2 operator - (Vector2 v);
	Vector2 operator * (Vector2 v);
	Vector2 operator / (float scale);
	bool operator != (Vector2 v);
	bool operator == (Vector2 v);
	Vector2 operator += (Vector2 v);
	Vector2 operator *= (Vector2 v);
	Vector2 operator -= (Vector2 v);
	Vector2 scale(float value); //scales vector by given value

	double length(); //calculates the length of this vector
};

