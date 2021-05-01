#pragma once

#include "Animation.h"

class Snake : public Animation
{
private:

	/////////뱀의 HP///////////
	int hp;

	/////////아이템 생성 여부///////
	bool makeItem;

public:
	Snake(float px, float py, bool makeItem);
	~Snake();

	void init();

	////////충돌 이벤트 오버라이딩/////
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);
};
