#pragma once
#include "Resource.h"
#include "Ball.h"

class Brick {
public:
	int x;
	int y;
	int height;
	int width;

	Brick(int x, int y, int height, int width);
	~Brick();
};