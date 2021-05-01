#pragma once

#include "Animation.h"

class Ninja : public Animation
{
	////////////�ִϸ��̼� ����////////////////
	enum State {idle=0, attack=1, hit=2};

private:

	///////////������ ��������//////////
	bool makeItem;

	State state;   //�ִϸ��̼� ����
	int    hp;     //���� ü�� ����

public:
	Ninja(float px, float py, bool makeItem);
	~Ninja();

	void init();
	void update();

	////////�浹 �̺�Ʈ �������̵�/////
	void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);  //�浹����
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);       //�浹��
	void OnCollisionExit(GameObject *obj, AABB * otherCol, AABB * myCol);   //�浹��

	////////�ִϸ��̼� �����ȯ �̺�Ʈ �������̵�////
	void OnFrameChange(int id, int frame);

	////////�ִϸ��̼� �׽�Ʈ �Լ�///////
	void aniTest();
};
