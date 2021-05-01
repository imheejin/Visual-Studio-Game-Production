#pragma once

#include "Animation.h"

class Scythe : public Animation 
{
private:

	////////���� �̵��ӵ�/////////
	float speed;

	///////���� �� ���� �Ÿ� �����ϱ�/////
	float moveDist; 

public:
	Scythe(float px, float py);
	~Scythe();

	void init();
	void update();

	//////////�浹 �̺�Ʈ �������̵�/////////
	void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);
	
};