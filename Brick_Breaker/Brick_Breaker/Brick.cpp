#pragma once
#include "Brick.h"

using namespace std;

Brick::Brick(int x, int y, int width, int height){ 
	m_x = x;
	m_y = y;
	this->width = width;
	this->height = height;
}

RECT Brick::getRect() {
	RECT rect;
	rect.left = m_x;
	rect.top = m_y;
	rect.right = m_x + 100;
	rect.bottom = m_y + 40;
	return rect;

}

void Brick::draw(HDC hdc__) {
	if (!isDestroyed) {
		Rectangle(hdc__, m_x, m_y, m_x + 100, m_y + 40);
	}
}

void Brick::destroy() {
	isDestroyed = true;
}

bool Brick::isHit() {
	return isDestroyed;
}