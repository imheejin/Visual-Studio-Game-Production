#include "stdafx.h"
#include "Rasengan.h"
#include "timer.h"
#include "GameObjectPool.h"
#include "Sound.h"

Rasengan::Rasengan(float px, float py) : Animation("라센간", 0, true, px, py)
{
}

Rasengan::~Rasengan()
{
}

void Rasengan::init()
{
	//////////애니메이션 로드///////////
	for (int i = 0; i < 3; i++)
	{
		Sprite sprite;

		readBmpRect("asset/라센간2.bmp", i*(107 + 2), 0, 107, 68, &sprite);

		/////////////스프라이트에 충돌체 추가하기//////////
		sprite.addCollider(new AABB(35, 15, 62, 53, 0), px, py);

		addFrame(sprite, 0);
	}

	//////////이동속도 초기화//////////
	speed = 150;

	//////////이동거리 측정변수 초기화//////
	moveDist=0;

	////////////효과음 추가하기////////////
	Sound * fx = new Sound();
	fx->play("asset/fx/fire1.wav", false);
	fx->setLifeTime(5);

	GameObjectPool::instance()->addGameObject(fx,0);

	////addChildObj(fx, 0);
}

void Rasengan::update()
{
	float dist = speed * getDelteTime();
	translate(dist, 0);

	////////////총 이동거리 측정하기////////
	moveDist = moveDist + dist;

	if (moveDist >= 250)
	{
		GameObjectPool * pool = GameObjectPool::instance();
		pool->delGameObject(this);
	}
}

void Rasengan::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	if (obj->getTag() == 1 && otherCol->getId()==0)  //적의 0 번충돌체일때..피해를 줌
	{
		//[1] 풀 객체 가져오기
		GameObjectPool * pool = GameObjectPool::instance();

		//[2] 풀에 있는 자신 객체(this)를 삭제함
		pool->delGameObject(this);  //라센건		
	}
}