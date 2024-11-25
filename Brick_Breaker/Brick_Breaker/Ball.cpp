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

void Ball::paddle_updatePosition(int paddle_left, int paddle_top, int paddle_right, int paddle_bottom) {
	if (y >= paddle_top && x >= paddle_left && x <= paddle_right)
	{
		//speedX = -speedX;
		speedY = -speedY;
	}
}
void Ball::brick_updatePosition(int brick_left, int brick_top, int brick_right, int brick_bottom) {
	// 공이 벽돌과 충돌했는지 확인
	if (x + width > brick_left && x < brick_right &&
		y + height > brick_top && y < brick_bottom) {

		// 충돌 방향을 판별하기 위해 공의 중심을 기준으로 계산
		int ballCenterX = x + width / 2;
		int ballCenterY = y + height / 2;

		// 벽돌의 중심과 공의 중심 간의 차이 계산
		int brickCenterX = (brick_left + brick_right) / 2;
		int brickCenterY = (brick_top + brick_bottom) / 2;

		int diffX = ballCenterX - brickCenterX;
		int diffY = ballCenterY - brickCenterY;

		// 충돌 방향을 판별
		if (abs(diffX) > abs(diffY)) {
			// 수평 방향 충돌
			speedX = -speedX;
		}
		else {
			// 수직 방향 충돌
			speedY = -speedY;
		}
	}
}


bool Ball::isInsideEllipse(int px, int py) {
	int h = x + width / 2;
	int k = y + height / 2;

	int a = width / 2;
	int b = height / 2;

	return (pow(px - h, 2) / pow(a, 2)) + (pow(py - k, 2) / pow(b, 2)) <= 1.0;
}