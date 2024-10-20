#include "Area.h"

void GameArea::makeSquare(HDC hdc) {
	Rectangle(hdc, GAME_AREA_LEFT, GAME_AREA_TOP, GAME_AREA_RIGHT, GAME_AREA_BOTTOM);
}