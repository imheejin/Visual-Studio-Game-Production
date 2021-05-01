#pragma once

#include "GameObject.h"
#include "AABB.h"

class ColPair
{
public:

	enum State { NotCol = 0, Col = 1 };  //NotCol�� �浹���� �浹�ȵ�, Col�� �浹��

private:
	////////�浹�� A ��ü�� �浹ü(AABB) ����//////
	GameObject * A; 
	AABB * aa;     

	///////�浹�� B ��ü�� �浹ü(AABB) ����///////
	GameObject *B;
	AABB  *ab;   

	//////�浹 ���� ����//////
	State state;

public:

	//////////////////������//////////////////////
	ColPair(GameObject *A, AABB * aa, GameObject *B, AABB *ab);
	virtual ~ColPair();

	///////���� �浹ü �������� �˻��ϴ� �Լ�///////
	bool isEqual(GameObject *A, AABB *aa, GameObject *B, AABB *ab);

	/////////////�浹 ���� ����/����///////////////
	void  SetState(State state);
	State GetState();

	/////////////�浹 �� ��ü/�浹ü..��������///////
	GameObject * GetGameObjectA();
	AABB       * GetAABBaa();

	GameObject * GetGameObjectB();
	AABB       * GetAABBab();
};