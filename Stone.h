#pragma once

#include "SpriteObject.h"

class Stone : public SpriteObject
{
private:

public:
	Stone(float px, float py);
	~Stone();

	void init();

	////////////�浹ü �̺�Ʈ �������̵�///////////////
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);
};
