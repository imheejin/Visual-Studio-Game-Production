#pragma once

#include "SpriteObject.h"

class Stone : public SpriteObject
{
private:

public:
	Stone(float px, float py);
	~Stone();

	void init();

	////////////충돌체 이벤트 오버라이딩///////////////
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);
};
