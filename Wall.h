#pragma once

#include "SpriteObject.h"


class Wall : public SpriteObject
{
private:
	//////////////���̵� ���� enum �����///////////
	enum State { up = 0, down = 1 };

	//////////�̵��ӵ�/////////	
	float upSpeed;   //[1]���� �̵��ӵ�
	float downSpeed; //[2]�Ʒ��� �̵� �ӵ�

	/////////���� ����/////////
	State state;

public:
	Wall(float px, float py);
	Wall(float px, float py, float upSpeed, float downSpeed, State state);
	~Wall();

	void init();
	void update();

	/////////////////////�浹ü �������̵�//////////////////////////
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);
};