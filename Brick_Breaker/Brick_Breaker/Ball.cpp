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
		speedX = -speedX; // x ���� ����
	}

	if (y + height >= area_bottom || y <= area_top) {
		speedY = -speedY; // y ���� ����
	}

	// x, y ������Ʈ
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
    // ���� ������ �浹�ߴ��� Ȯ��
    if (x + width > brick_left && x < brick_right && y + height > brick_top && y < brick_bottom) {
        // ���� �߽� ��ǥ ���
        int ballCenterX = x + width / 2;
        int ballCenterY = y + height / 2;

        // ������ �� ���� �� �߽� ���� �Ÿ� ���
        int distLeft = abs(ballCenterX - brick_left);
        int distRight = abs(ballCenterX - brick_right);
        int distTop = abs(ballCenterY - brick_top);
        int distBottom = abs(ballCenterY - brick_bottom);

        // ���� ª�� �Ÿ��� �浹 ���� �Ǻ�
        if (distLeft < distRight && distLeft < distTop && distLeft < distBottom) {
            // ���� ���� �浹
            speedX = -speedX;
     // �� ��ġ ����
        } else if (distRight < distLeft && distRight < distTop && distRight < distBottom) {
            // ������ ���� �浹
            speedX = -speedX;
            //x = brick_right; // �� ��ġ ����
        } else if (distTop < distBottom) {
            // ���� ���� �浹
            speedY = -speedY;
            //y = brick_top - height; // �� ��ġ ����
        } else {
            // �Ʒ��� ���� �浹
            speedY = -speedY;
            //y = brick_bottom; // �� ��ġ ����
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