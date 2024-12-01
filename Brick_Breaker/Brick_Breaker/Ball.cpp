#include "Ball.h"


Ball::Ball(int x, int y, int width, int height,double speedX, double speedY) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->speedX = speedX;
	this->speedY = speedY;
}

Ball::~Ball() {

}

void Ball::area_updatePosition(int area_left, int area_top, int area_right, int area_bottom, HWND hWnd, Ball ball) {
    if (x + width >= area_right || x <= area_left) {
        speedX = -speedX; // x 방향 반전
    }

    if (y <= area_top) {
        speedY = -speedY; // y 방향 반전
    }

    if (y + height >= area_bottom) {
        if (!isGameOver) {  // 게임 오버 상태가 아닐 때만 처리
            // 게임 오버 처리
            isGameOver = true;
            MessageBox(hWnd, L"게임 오버!", L"Game Over", MB_OK);
            // 타이머 종료
            KillTimer(hWnd, 1);
            // 공 객체 삭제
        }
        return; // 공 이동 중단
    }

    // x, y를 double 기반으로 계산 후 정수 변환
    x += static_cast<int>(speedX);
    y += static_cast<int>(speedY);
}
void Ball::paddle_updatePosition(int paddle_left, int paddle_top, int paddle_right, int paddle_bottom) {
    // 공이 패들과 충돌했는지 확인
    if (y + height >= paddle_top && y <= paddle_bottom && x + width >= paddle_left && x <= paddle_right) {
        // 패들의 중심 계산
        int paddleCenter = (paddle_left + paddle_right) / 2;

        // 공의 중심 계산
        int ballCenter = x + width / 2;

        // 충돌 위치에 따른 오프셋 계산
        int offset = ballCenter - paddleCenter;

        // 속도의 크기 유지
        double speedMagnitude = sqrt(speedX * speedX + speedY * speedY);

        // 각도 조정 (오프셋을 기반으로 -45도 ~ +45도 사이의 각도를 설정)
        double maxAngle = 3.14159 / 4.0; // 최대 45도 (3.14159 / 4.0)
        double angle = (offset / (double)((paddle_right - paddle_left) / 2)) * maxAngle;

        // 새로운 X축, Y축 속도 계산
        speedX = speedMagnitude * sin(angle);
        speedY = -speedMagnitude * cos(angle); // 항상 위로 반사
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