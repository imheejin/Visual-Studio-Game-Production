#include "stdafx.h"
#include "Scythe.h"
#include "timer.h"
#include "GameObjectPool.h"

Scythe::Scythe(float px, float py) : Animation("큰낫", 1, true, px, py)
{
}

Scythe::~Scythe()
{
}

void Scythe::init()
{
	////////애니메이션 로드하기////////
	for (int i = 0; i < 4; i++)
	{
		Sprite sprite;

		readBmpRect("asset/닌자.bmp", i*(40 + 2), 418, 40, 40, &sprite);

		//////////////충돌체 추가하기/////////////
		sprite.addCollider(new AABB(10, 10, 20, 20, 0), px, py);

		addFrame(sprite, 0);
	}

	//////////애니메니션 속도 지정하기//////////
	setFrameDelay(0.05);

	//////////////이동속도 지정하기/////////////
	speed = 150;

	//////////////총 이동거리 초기화 하기////////
	moveDist = 0;

}

void Scythe::update()
{		
	float dist = speed * getDelteTime();
	translate(-dist, 0);

	//////////낫의 총이동거리 구하기//////////
	moveDist = moveDist + dist;

	if (moveDist >= 200)
	{
		GameObjectPool * pool = GameObjectPool::instance();
		pool->delGameObject(this);
	}

}

///////////////충돌 시작 검사하기//////////////
void Scythe::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)  
{
	if (strcmp(obj->getName(), "나루토") == 0)
	{
		/////////낫 제거하기///////
		GameObjectPool * pool = GameObjectPool::instance();
		pool->delGameObject(this);
	}
}