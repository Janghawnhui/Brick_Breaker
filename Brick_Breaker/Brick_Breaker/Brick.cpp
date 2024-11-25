#pragma once
#include "Brick.h"

using namespace std;

Brick::Brick(int x, int y){ 
	m_x = x;
	m_y = y;
}

RECT getRect() {
	RECT recct = { left}
}

void Brick::draw(HDC hdc__) {
	Rectangle(hdc__, m_x, m_y, m_x + 100, m_y + 40);

}