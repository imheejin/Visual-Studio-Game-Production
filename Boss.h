#pragma once

#include "Animation.h"

class Boss : public Animation
{
private:

	enum State{ walk, attack1, attack2, death};
	
	int hp;		   ///////hp ����///////
	State state;   //���� ���� ����

	float speed;       //������ �̵� �ӵ�
	float attackDist;  //������ ���� �Ÿ�

	float attack1Delay; //ù��° ���� ���ӽð�

public:

	Boss(float px, float py);
	~Boss();

	void init();
	void update();

	////////�浹 �̺�Ʈ �������̵�/////
	void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);

	////////�ִϸ��̼� �����̺�Ʈ//////
	void OnFrameChange(int id, int frameNum);

	void aniTest();
};