#include "Ball.h"


Ball::Ball(int x, int y, int width, int height, int speed) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->speed = speed;
}

Ball::~Ball() {

}

bool Ball::isInsideEllipse(int px, int py) {
	int h = x + width / 2;
	int k = y + height / 2;

	int a = width / 2;
	int b = height / 2;

	return (pow(px - h, 2) / pow(a, 2)) + (pow(py - k, 2) / pow(b, 2)) <= 1.0;
}