#pragma once

#include "GameObject.h"
#include "AABB.h"

class ColPair
{
public:

	enum State { NotCol = 0, Col = 1 };  //NotCol은 충돌아직 충돌안됨, Col은 충돌됨

private:
	////////충돌한 A 객체와 충돌체(AABB) 정보//////
	GameObject * A; 
	AABB * aa;     

	///////충돌한 B 객체와 충돌체(AABB) 정보///////
	GameObject *B;
	AABB  *ab;   

	//////충돌 상태 변수//////
	State state;

public:

	//////////////////생성자//////////////////////
	ColPair(GameObject *A, AABB * aa, GameObject *B, AABB *ab);
	virtual ~ColPair();

	///////같은 충돌체 쌍인지를 검사하는 함수///////
	bool isEqual(GameObject *A, AABB *aa, GameObject *B, AABB *ab);

	/////////////충돌 상태 세터/게터///////////////
	void  SetState(State state);
	State GetState();

	/////////////충돌 쌍 객체/충돌체..가져오기///////
	GameObject * GetGameObjectA();
	AABB       * GetAABBaa();

	GameObject * GetGameObjectB();
	AABB       * GetAABBab();
};