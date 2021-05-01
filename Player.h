#pragma once

#include "Animation.h"

class Player : public Animation
{
private:
	
	////////////////////�ִϸ��̼� ����//////////////////
	enum State { run = 0, jump = 1, attack = 2, hit=3 };

	////////�̵� �ӵ�/////////
	float runSpeed;  //run �̵��ӵ�
	float jumpSpeed; //jump �̵��ӵ�

	/////�ִϸ��̼� ����/////
	State state;

	//////ü�� ���� �߰��ϱ�//////
	//int hp;

public:
	Player(float px, float py);
	~Player();

	////////�÷��̾� �ʱ�ȭ/////////
	void init();

	/////////�÷��̾� ������Ʈ///////
	void update();

	////////�浹 �̺�Ʈ �������̵�/////
	void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);

	////////�ִϸ��̼� �׽�Ʈ �Լ�/////
	void AniTest();
};