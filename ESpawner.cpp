#include "stdafx.h"
#include "ESpawner.h"
#include "NinjaEffect.h"

ESpawner::ESpawner(float px, float py) : GameObject("적생성객체", 1, true, px, py)
{
}

ESpawner::~ESpawner()
{
}

void ESpawner::init()
{
	////////닌자 생성 위치 초기화//////////////////
	ninjaPx[0] = 450;
	ninjaPy[0] = 90;

	ninjaPx[1] = 1900;
	ninjaPy[1] = 120;

	ninjaPx[2] = 2800;
	ninjaPy[2] = 120;

	//////아이템 생성 여부 배열 초기화 ///////////
	makeItem[0] = false;
	makeItem[1] = false;
	makeItem[2] = true;

	///////닌자를 출현을 위한 충돌체 추가하기//////
	addCollider(new AABB(ninjaPx[0] -250, ninjaPy[0] -40, 20, 90, 0));
	addCollider(new AABB(ninjaPx[1] -250, ninjaPy[1] -40, 20, 90, 1));
	addCollider(new AABB(ninjaPx[2] -250, ninjaPy[2] -40, 20, 90, 2));
}

void ESpawner::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	if (strcmp(obj->getName(), "나루토") == 0 && myCol->getId() == 0)
	{
		//[1]닌자 효과 객체 추가하기 - 배경객체에 추가함
		parentObj->addChildObj(new NinjaEffect(ninjaPx[0], ninjaPy[0], makeItem[0]), 3);  //객체 생성자 수정

		//[2]충돌체를 제거함
		delCollider(0);
	}

	if (strcmp(obj->getName(), "나루토") == 0 && myCol->getId() == 1)
	{
		//[1]닌자 효과 객체 추가하기 - 배경객체에 추가함
		parentObj->addChildObj(new NinjaEffect(ninjaPx[1], ninjaPy[1], makeItem[1]), 3); //객체 생성자 수정

		//[2]충돌체를 제거함
		delCollider(1);
	}

	if (strcmp(obj->getName(), "나루토") == 0 && myCol->getId() == 2)
	{
		//[1]닌자 효과 객체 추가하기 - 배경객체에 추가함
		parentObj->addChildObj(new NinjaEffect(ninjaPx[2], ninjaPy[2], makeItem[2]), 3); //객체 생성자 수정

		//[2]충돌체를 제거함
		delCollider(2);
	}
}