#include "stdafx.h"
#include "Ninja.h"
#include "input.h"
#include "Scythe.h"
#include "GameObjectPool.h"
#include "NinjaDeath.h"
#include "FlyingLabel.h"
#include "GameManager.h"

Ninja::Ninja(float px, float py, bool makeItem) : Animation("닌자", 1, true, px, py)
{
	this->makeItem = makeItem;
}

Ninja::~Ninja()
{
}

void Ninja::init()
{
	//////////애니메이션 로드하기-idle 애니메이션 //////////
	for (int i = 0; i < 4; i++)
	{
		Sprite sprite;

		readBmpRect("asset/닌자.bmp", i*(42 + 2), 0, 42, 49, &sprite);

		/////////////////충돌체 추가하기////////////////
		sprite.addCollider(new AABB(0, 0, 33, 49,    0), px, py); //플레이어 공격 감지

		sprite.addCollider(new AABB(-160, 0, 195, 49, 1), px, py); //플레이어 접근 감지

		addFrame(sprite, idle);
	}

	//////////애니메이션 로드하기-attack 애니메이션//////////
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBmpRect("asset/닌자.bmp", i*(56 + 2), 51, 56, 48, &sprite);

		/////////스트라이트 앵커포인트 조정하기///////////
		sprite.ax = 20;

		/////////////////충돌체 추가하기////////////////
		sprite.addCollider(new AABB(-10, 5, 38, 44, 0), px, py); //플레이어 공격 감지

		sprite.addCollider(new AABB(-180, 5, 208, 44, 2), px, py); //플레이어 멀어짐 감지

		addFrame(sprite, attack);
	}

	///////////////애니메이션 로드하기 - hit 애니메이션////////
	for (int i = 0; i < 2; i++)
	{
		Sprite sprite;

		readBmpRect("asset/닌자.bmp", i*(41 + 2), 218, 41, 56, &sprite);
		addFrame(sprite, hit);    //닌자 피해(hit)애니메이션 추가하기
	}

	//////////////애니메이션 상태 초기화///////////
	state = idle;
	play(state);

	//////////////닌자 hp 초기화//////////////////
	hp = 100;

}

void Ninja::update()
{
}

void Ninja::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	GameObjectPool * pool = GameObjectPool::instance();

	///////플레이어가 닌자에 접근 검사 - 공격범위에 들어왔는지 체크/////////
	if (strcmp(obj->getName(), "나루토") == 0 && myCol->getId() == 1)  //닌자의 1 번충돌체
	{
		state = attack;
		play(attack);
		setFrameDelay(0.25);
	}
	
	////////////////닌자가 라센건에..맞으면..hp 감소 시키기////////////////
	if (strcmp(obj->getName(), "라센간") == 0 && myCol->getId() == 0)
	{
		/////////////////닌자 hit 애니메이션 전환하기//////////////
		state = hit;
		play(hit);

		/////////////////닌자 체력 감소시키기/////////////////////
		hp = hp - 50;
		
		////////////////Flying 레이블 만들기//////////////////////
		pool->addGameObject(new FlyingLabel(L"체력: -50", 0x00ff0000, px, py), 3);

		if (hp < 0)
		{
			//////////체력이 모두 소진되면..닌자를 제거함-자식으로 추가되면..자식객체 지우기를 해야함////////////
			parentObj->delChildObj(this);

			/////////닌자 죽음 애니메이션 객체 생성////////////
			parentObj->addChildObj(new NinjaDeath( getXFromParent(),  getYFromParent(), makeItem ), 2);  //스크롤된 부모 객체를 기준으로 좌표 지정

			/////////점수 올리기-Flying 레이블 만들기///////////
			GameManager * manager = GameManager::instance();

			pool->addGameObject(new FlyingLabel(L"점수: +20", 0x0000ff00, px+10, py+30), 3);
			manager->addScore(20);
		}
	}
}

void Ninja::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
}

void Ninja::OnCollisionExit(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	///////////////플레이어가 공격 범위를 벗어났는지를 검사////////////
	if (strcmp(obj->getName(), "나루토") == 0 && myCol->getId() == 2)
	{
		state = idle;
		play(idle);
		setFrameDelay(0.1);
	}
}

void Ninja::OnFrameChange(int id, int frame)
{
	if (id == attack && frame == 3)
	{
		GameObjectPool * pool = GameObjectPool::instance();
		pool->addGameObject(new Scythe(px-20, py+10), 2);
	}

	//////////hit 애니메이션 원상복구하기//////////
	if (id == hit && frame == 0)
	{
		/////////idle 애니메이션으로 복구함//////////
		state = idle;
		play(idle);

		setFrameDelay(0.1);  //애니메이션속도..복구
	}
}

void Ninja::aniTest()
{
	if (getKeyUp('1') == true)
	{
		play(idle);
	}

	if (getKeyUp('2') == true)
	{
		play(attack);
	}
}