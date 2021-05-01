#pragma once

#include "Animation.h"

class Rasengan : public Animation
{
private:

	///////////이동속도//////////
	float speed;

	///////////총 이동거리 변수///////
	float moveDist;

public:
	Rasengan(float px, float py);
	~Rasengan();

	void init();
	void update();

	////////충돌 이벤트 오버라이딩/////
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);
};
