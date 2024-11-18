#include "Ball.h"


Ball::Ball(int x, int y, int width, int height,int speedX, int speedY) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->speedX = speedX;
	this->speedY = speedY;
}

Ball::~Ball() {

}

void Ball::area_updatePosition(int area_left, int area_top, int area_right, int area_bottom) {

	if (x + width >= area_right || x <= area_left) {
		speedX = -speedX; // x 방향 반전
	}

	if (y + height >= area_bottom || y <= area_top) {
		speedY = -speedY; // y 방향 반전
	}

	// x, y 업데이트
	x += speedX;
	y += speedY;
}

void Ball::paddle_updatePosition(int paddle_left, int paddle_top, int paddle_rigght, int paddle_bottom) {

}
bool Ball::isInsideEllipse(int px, int py) {
	int h = x + width / 2;
	int k = y + height / 2;

	int a = width / 2;
	int b = height / 2;

	return (pow(px - h, 2) / pow(a, 2)) + (pow(py - k, 2) / pow(b, 2)) <= 1.0;
}