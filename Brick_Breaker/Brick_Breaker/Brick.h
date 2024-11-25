#pragma once
#include "Resource.h"
#include "Ball.h"
#include <vector>
using namespace std;

class Brick {
public:
	int m_array[4][10];
	//vector<int> m_array;
	int m_x;
	int m_y;
	int width;
	int height;

	bool isDestroyed=false;
	Brick(int x, int y, int width, int height);

	void draw(HDC hdc__);

	void destroy();

	bool isHit();
	RECT getRect();
};