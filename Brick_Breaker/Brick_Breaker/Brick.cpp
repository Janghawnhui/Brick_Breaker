#pragma once
#include "Brick.h"
//std::vector<Item*> activeItems;

Brick::Brick(int x, int y, int width, int height){ 
	m_x = x;
	m_y = y;
	this->width = width;
	this->height = height;
}

RECT Brick::getRect() {
	RECT rect;
	rect.left = m_x;
	rect.top = m_y;
	rect.right = m_x + 100;
	rect.bottom = m_y + 40;
	return rect;

}

void Brick::draw(HDC hdc__) {
	if (!isDestroyed) {
		Rectangle(hdc__, m_x, m_y, m_x + 100, m_y + 40);
	}
}

void Brick::destroy() {
	isDestroyed = true;

	//// 랜덤으로 아이템 생성
	//if (rand() % 2 == 0) {
	//	int itemType = rand() % 2 + 1; // 아이템 타입 (1 또는 2)
	//	item = new Item(m_x + width / 2 - 10, m_y + height, itemType);
	//	activeItems.push_back(item); // 전역 벡터에 추가
	//}
}


bool Brick::isHit() {
	return isDestroyed;
}

Item* Brick::releaseItem() {
	if (item != nullptr && !item->isActive) {
		Item* releasedItem = item;
		item = nullptr; // 아이템 반환 후 초기화
		return releasedItem;
	}
	return nullptr;
}