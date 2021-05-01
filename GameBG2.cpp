#include "stdafx.h"
#include "GameBG2.h"
#include "timer.h"
#include "graphic.h"
#include "Stone.h"
#include "Wall.h"
#include "Snake.h"
#include "ESpawner.h"
#include "GameManager.h"

GameBG2::GameBG2(float px, float py):SpriteObject("배경2", 2, true, px, py)
{
}

GameBG2::~GameBG2()
{
}

void GameBG2::init()
{
	//////////배경이미지 로드/////////
	readBmp("asset/배경2.bmp", &sprite);

	//////////배경 충돌체 추가하기//////
	addCollider(new AABB(0,   141, 608,  55, 0));
	addCollider(new AABB(609, 171, 2567, 55, 0));

	addCollider(new AABB(2977, 75, 131, 117, 1));  //보스 등장 시키는 충돌체

	//////////스톤 달기-자식게임 오브젝트 추가///////
	addChildObj(new Stone(1000, 140), 2);
	addChildObj(new Stone(1570, 140), 2);
	addChildObj(new Stone(2070, 140), 2);

	//////////움직이는 벽 달기 - 자식게임 오브젝트 추가/////
	addChildObj(new Wall(1370, 140), 2);
	addChildObj(new Wall(2250, 140), 2);

	//////////////////뱀 추가하기 //////////////////
	addChildObj(new Snake(445,  100, false), 2);	
	addChildObj(new Snake(950,  130, true), 2);
	addChildObj(new Snake(1800, 130, false), 2);
	
	/////////////////적 생성객체(Spawner) 추가하기//////
	addChildObj(new ESpawner(0, 0), 1);

	//////////////이동속도 초기화///////////////////
	speed = 20;
}

void GameBG2::update()
{	
	float dist = speed * getDelteTime();
	translate(-dist, 0);	
}

void GameBG2::translate(float dx, float dy)
{
	/***********************************/
	int imgWidth = sprite.width;
	int scrWidth = getClientWidth();

	//이미지의 px 는 최소 -(imgWidth - scrWidth)까지 감소 가능

	int minPx = -(imgWidth - scrWidth);

	if (px > minPx)
	{		
		GameObject::translate(dx, dy);
	}
}

void GameBG2::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	if (strcmp(obj->getName(), "나루토") == 0 && myCol->getId()==0)  //플레이어를 지형 위로 올림
	{
		//////////플레이어 바운딩박스 좌표 가져오기/////////////////
		float x0, y0, x1, y1;
		otherCol->getBB(x0, y0, x1, y1);

		/////////배경의 바운딩박스 좌표 가져오기////////////////////
		float a0, b0, a1, b1;
		myCol->getBB(a0, b0, a1, b1);

		//////////////플레이어 위로 올리기/////////////////////////
		float h = y1 - b0;

		obj->translate(0, -h);

	}
	else if (strcmp(obj->getName(), "나루토") == 0 && myCol->getId() == 1) {

		//////////플레이어 바운딩박스 좌표 가져오기/////////////////
		float x0, y0, x1, y1;
		otherCol->getBB(x0, y0, x1, y1);

		/////////배경의 바운딩박스 좌표 가져오기////////////////////
		float a0, b0, a1, b1;
		myCol->getBB(a0, b0, a1, b1);

		////////////////플레이어 뒤로 보내기//////////////////////
		float w = x1 - a0;
		obj->translate(-w, 0);

		///////////////보스 스폰하기//////////////////////////////
		GameManager::instance()->bossSpawn();

		//printf("보스 등장\n");

		///////////////충돌체 제거하기////////////////////////////
		delCollider(1);
	}
	
}