#include "stdafx.h"
#include "ColPair.h"

ColPair::ColPair(GameObject *A, AABB * aa, GameObject *B, AABB *ab)
{
	this->A  = A;
	this->aa = aa;
	
	this->B  = B;
	this->ab = ab;

	this->state = Col;  //충돌이 된상태로 지정함
}


ColPair::~ColPair()
{
}

bool ColPair::isEqual(GameObject *A, AABB *aa, GameObject *B, AABB *ab)
{
	if ( (this->A == A && this->aa->getId() == aa->getId() && this->B == B && this->ab->getId() == ab->getId()) ||
		 (this->A == B && this->aa->getId() == ab->getId() && this->B == A && this->ab->getId() == aa->getId()) )
	{
		return true;
	}
		return false;
}

void ColPair::SetState(State state)
{
	this->state = state;
}

ColPair::State ColPair::GetState()
{
	return state;
}

GameObject * ColPair::GetGameObjectA()
{
	return A;
}

AABB * ColPair::GetAABBaa()
{
	return aa;
}

GameObject * ColPair::GetGameObjectB()
{
	return B;
}

AABB * ColPair::GetAABBab()
{
	return ab;
}