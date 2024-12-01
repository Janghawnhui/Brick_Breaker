#pragma once
#include <windows.h>

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