#pragma once
#include "Item.h"

Item::Item(int x, int y, int type) {
	this->x = x;
	this->y = y;
	this->type = type;
}

void Item::updatePoisition() {
	if (isActive) {
		y += 5;
	}
}
void Item::draw(HDC hdc) {
	if (isActive) {
		// 아이템 종류에 따라 색상 변경
		HBRUSH hBrush = CreateSolidBrush(type == 1 ? RGB(255, 0, 0) : RGB(0, 255, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, x, y, x + width, y + height);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
	}
}