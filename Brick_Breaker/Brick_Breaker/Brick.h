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

	Brick(int x, int y);

	void draw(HDC hdc__);

};