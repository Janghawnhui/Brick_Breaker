#pragma once
#include "Paddle.h"

Paddle::Paddle(int x, int y, int width, int height) {
	this->x = x;			//패들의 x 좌표 초기화
	this->y = y;			//패들의 y 좌표 초기화
	this->width = width;	//패들의 너비 초기화
	this->height = height;	//패들의 높이 초기화
}

Paddle::~Paddle() {

}

void Paddle::move(int mouseX) {
	x = mouseX - (width / 2);
	
	if (x < 10) {
		x = 10;
	}
	
	if (x + width > 1100) {
		x =	1100 - width;
	}
}

void Paddle::draw(HDC hdc) {
	Rectangle(hdc, x, y, x + width, y + height);
}

RECT Paddle::getRect() {
	RECT rect;
	rect.left = x;
	rect.top =y;
	rect.right = x + width;
	rect.bottom = y + height;
	return rect;
}

//DWORD WINAPI Paddle::Paddle_Thread(LPVOID param) {
//	x = LOWORD(param) - (width / 2);
//	if (x < 10) {
//		x = 10;
//	}
//
//	if (x + width > 1100) {
//		x = 1100 - width;
//	}
//}