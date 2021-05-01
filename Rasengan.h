#pragma once

#include "Animation.h"

class Rasengan : public Animation
{
private:

	///////////�̵��ӵ�//////////
	float speed;

	///////////�� �̵��Ÿ� ����///////
	float moveDist;

public:
	Rasengan(float px, float py);
	~Rasengan();

	void init();
	void update();

	////////�浹 �̺�Ʈ �������̵�/////
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);
};
