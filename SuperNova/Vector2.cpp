#include "Vector2.h"
#include <math.h>

Vector2::Vector2() {}

Vector2::Vector2(float x, float y)
	:x(x), y(y)
{}

Vector2 Vector2::operator + (Vector2 v) {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator - (Vector2 v) {
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator * (Vector2 v) {
	return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::operator / (float scale) {
	return Vector2(x / scale, y / scale);
}

bool Vector2::operator != (Vector2 v) {
	if (v.x != x || v.y != y) {
		return false;
	}
	return true;
}

bool Vector2::operator == (Vector2 v) {
	if (v.x == x && v.y == y) {
		return true;
	}
	return false;
}

Vector2 Vector2::operator += (Vector2 v) {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator *= (Vector2 v) {
	return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::operator -= (Vector2 v) {
	return Vector2(x - v.x, y - v.y);
}

Vector2::Vector2::scale(float value) {
	return Vector2(x * scale, y * scale);
}

double Vector2::length(Vector2 v) {
	return sqrt(pow(x, 2) + pow(y, 2));
}