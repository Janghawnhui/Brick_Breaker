#pragma once
#include <windows.h>
#include <vector>

class Item {
public:
	int x, y;
	int width, height;
	bool isActive;
	int type;
	
	Item(int x, int y, int type);

	void updatePoisition();
	void draw(HDC hdc);

};