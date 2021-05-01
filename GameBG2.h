#pragma once

#include "SpriteObject.h"

class GameBG2 : public SpriteObject
{
private:

	/////////�̵� �ӵ�//////////
	float speed;

public:
	GameBG2(float px, float py);
	~GameBG2();

	void init();
	void update();

	//////////////////�浹 �̺�Ʈ �������̵�//////////////////////////
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);

	///////////////////translate �������̵�//////////////////////////
	void translate(float dx, float dy);
};