#pragma once

#include "Animation.h"

class Snake : public Animation
{
private:

	/////////���� HP///////////
	int hp;

	/////////������ ���� ����///////
	bool makeItem;

public:
	Snake(float px, float py, bool makeItem);
	~Snake();

	void init();

	////////�浹 �̺�Ʈ �������̵�/////
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);
};
