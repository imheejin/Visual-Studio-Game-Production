#pragma once

#include "Animation.h"

class Scythe : public Animation 
{
private:

	////////낫의 이동속도/////////
	float speed;

	///////낫이 총 날라간 거리 측정하기/////
	float moveDist; 

public:
	Scythe(float px, float py);
	~Scythe();

	void init();
	void update();

	//////////충돌 이벤트 오버라이딩/////////
	void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);
	
};