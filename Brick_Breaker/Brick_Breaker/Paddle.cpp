#pragma once
#include "Paddle.h"

Paddle::Paddle(int x, int y, int width, int height) {
	this->x = x;			//�е��� x ��ǥ �ʱ�ȭ
	this->y = y;			//�е��� y ��ǥ �ʱ�ȭ
	this->width = width;	//�е��� �ʺ� �ʱ�ȭ
	this->height = height;	//�е��� ���� �ʱ�ȭ
}

Paddle::~Paddle() {

}

void Paddle::move(int mouseX) {
	x = mouseX - (width / 2);
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