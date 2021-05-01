#include "stdafx.h"
#include "Snake.h"
#include "SnakeDeath.h"
#include "GameObjectPool.h"
#include "FlyingLabel.h"
#include "GameManager.h"

Snake::Snake(float px, float py, bool makeItem) : Animation("뱀", 1, true, px, py)
{
	/////아이템 생성 여부//////
	this->makeItem = makeItem;
}

Snake::~Snake()
{
}

void Snake::init()
{
	///////////애니메이션 로드하기//////////
	for (int i = 0; i < 12; i++)
	{
		Sprite sprite;

		readBmpRect("asset/뱀.bmp", i*(53 + 2), 0, 53, 40, &sprite);

		/////////////충돌체 추가하기///////////
		sprite.addCollider(new AABB(10, 5, 43, 35, 0), px, py);

		/////////////애니메이션 추가//////////
		addFrame(sprite, 0);
	}

	////////////뱀의 초기 HP ////////////////
	hp = 50;
}

void Snake::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	GameObjectPool * pool = GameObjectPool::instance();

	////////라센건과 충돌 체크하기///////////
	if (obj->getTag() == 0 && strcmp( obj->getName(), "라센간") ==0)
	{
		hp = hp - 20;

		////////////////Flying 레이블 만들기//////////////////////
		pool->addGameObject(new FlyingLabel(L"체력: -20", 0x00ff0000, px, py), 3);

		if (hp < 0)
		{
			////////////////뱀 제거하기-자식오브젝트 제거//////////////
			parentObj->delChildObj(this);  //parnetObj는 배경, this는 뱀

			//////////////뱀 죽음 애니메이션-배경의 자식으로 추가///////
			parentObj->addChildObj(new SnakeDeath(getXFromParent(), getYFromParent(), makeItem), 2);

			/////////점수 올리기-Flying 레이블 만들기///////////
			GameManager * manager = GameManager::instance();

			pool->addGameObject(new FlyingLabel(L"점수: +10", 0x0000ff00, px + 10, py + 30), 3);
			manager->addScore(10);
		}
	}
}