#pragma once
#include <windows.h>
#include "Resource.h"
#include "framework.h"

class Paddle {
private:
    int x;         // 패들의 x 좌표
    int y;         // 패들의 y 좌표
    int width;     // 패들의 너비
    int height;    // 패들의 높이

public:
    Paddle(int x, int y, int width, int height);
    ~Paddle();

    void move(int mouseX); // direction: -1 (왼쪽), 1 (오른쪽)
    void draw(HDC hdc);       // 패들을 그리는 메서드
    RECT getRect();           // 패들의 사각형 영역을 반환


};
