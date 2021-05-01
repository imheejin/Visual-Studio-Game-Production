#pragma once

#include "SpriteObject.h"

class GameBG2 : public SpriteObject
{
private:

	/////////이동 속도//////////
	float speed;

public:
	GameBG2(float px, float py);
	~GameBG2();

	void init();
	void update();

	//////////////////충돌 이벤트 오버라이딩//////////////////////////
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);

	///////////////////translate 오버라이딩//////////////////////////
	void translate(float dx, float dy);
};