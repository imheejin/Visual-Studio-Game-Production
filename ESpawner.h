#pragma once

#include "GameObject.h"

#define MAX_NINJA 3

class ESpawner : public GameObject
{
private:

	///////////난자 생성 위치////////
	int ninjaPx[3];
	int ninjaPy[3];

	///////////아이템 생성 여부 배열///////
	bool makeItem[3];

public:
	ESpawner(float px, float py);
	~ESpawner();

	/////////init 오버라이딩////////
	void init();

	////////충돌 이벤트 오버라이딩/////
	void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);

};
