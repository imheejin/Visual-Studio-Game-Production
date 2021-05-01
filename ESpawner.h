#pragma once

#include "GameObject.h"

#define MAX_NINJA 3

class ESpawner : public GameObject
{
private:

	///////////���� ���� ��ġ////////
	int ninjaPx[3];
	int ninjaPy[3];

	///////////������ ���� ���� �迭///////
	bool makeItem[3];

public:
	ESpawner(float px, float py);
	~ESpawner();

	/////////init �������̵�////////
	void init();

	////////�浹 �̺�Ʈ �������̵�/////
	void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);

};
