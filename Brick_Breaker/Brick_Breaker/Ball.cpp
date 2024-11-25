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
	if (y >= paddle_top && x >= paddle_left && x <= paddle_right && y <= paddle_bottom)
	{
		//speedX = -speedX;
		speedY = -speedY;
	}
}

void Ball::brick_updatePosition(int brick_left, int brick_top, int brick_right, int brick_bottom) {
    // 공이 벽돌과 충돌했는지 확인
    if (x + width > brick_left && x < brick_right && y + height > brick_top && y < brick_bottom) {
        // 공의 중심 좌표 계산
        int ballCenterX = x + width / 2;
        int ballCenterY = y + height / 2;

        // 벽돌의 네 변과 공 중심 간의 거리 계산
        int distLeft = abs(ballCenterX - brick_left);
        int distRight = abs(ballCenterX - brick_right);
        int distTop = abs(ballCenterY - brick_top);
        int distBottom = abs(ballCenterY - brick_bottom);

        // 가장 짧은 거리로 충돌 방향 판별
        if (distLeft < distRight && distLeft < distTop && distLeft < distBottom) {
            // 왼쪽 변과 충돌
            speedX = -speedX;
     // 공 위치 조정
        } else if (distRight < distLeft && distRight < distTop && distRight < distBottom) {
            // 오른쪽 변과 충돌
            speedX = -speedX;
            //x = brick_right; // 공 위치 조정
        } else if (distTop < distBottom) {
            // 위쪽 변과 충돌
            speedY = -speedY;
            //y = brick_top - height; // 공 위치 조정
        } else {
            // 아래쪽 변과 충돌
            speedY = -speedY;
            //y = brick_bottom; // 공 위치 조정
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