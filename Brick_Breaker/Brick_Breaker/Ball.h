#pragma once
#include <windows.h>
#include "Resource.h"
#include "framework.h"

class Ball {
private:
	int x;
	int y;
	int width;
	int height;
	int speed;

public:
	Ball(int x, int y, int width, int height, int speed);
	~Ball();

	bool isInsideEllipse(int px, int py);
};