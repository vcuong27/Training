#pragma once
#include "Math.h"

class Rect
{
public:
	Rect() {};
	Rect(Vector2& pos, Vector2& distane);
	Vector2 _pos;
	Vector2 _distane;
};