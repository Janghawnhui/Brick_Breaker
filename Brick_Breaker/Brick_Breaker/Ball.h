#pragma once
#include <windows.h>
#include "Resource.h"
#include "framework.h"

class Ball {
public:
	int x;
	int y;
	int width;
	int height;
	int speedX;
	int speedY;


	Ball(int x, int y, int width, int height, int speedX, int speedY);
	~Ball();

	void area_updatePosition(int area_left, int area_top, int area_right, int area_bottom);
	void paddle_updatePosition(int paddle_left, int paddle_top, int paddle_right, int paddle_bottom);
	void brick_updatePosition(int brick_left, int brick_top, int brick_right, int brick_bottom);
	bool isInsideEllipse(int px, int py);
};