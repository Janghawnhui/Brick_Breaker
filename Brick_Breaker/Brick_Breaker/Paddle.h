#pragma once
#include <windows.h>
#include "Resource.h"
#include "framework.h"

class Paddle {
private:
    int x;         // �е��� x ��ǥ
    int y;         // �е��� y ��ǥ
    int width;     // �е��� �ʺ�
    int height;    // �е��� ����

public:
    Paddle(int x, int y, int width, int height);
    ~Paddle();

    void move(int mouseX); // direction: -1 (����), 1 (������)
    void draw(HDC hdc);       // �е��� �׸��� �޼���
    RECT getRect();           // �е��� �簢�� ������ ��ȯ


};
