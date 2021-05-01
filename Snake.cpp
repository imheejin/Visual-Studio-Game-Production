#include "stdafx.h"
#include "Snake.h"
#include "SnakeDeath.h"
#include "GameObjectPool.h"
#include "FlyingLabel.h"
#include "GameManager.h"

Snake::Snake(float px, float py, bool makeItem) : Animation("��", 1, true, px, py)
{
	/////������ ���� ����//////
	this->makeItem = makeItem;
}

Snake::~Snake()
{
}

void Snake::init()
{
	///////////�ִϸ��̼� �ε��ϱ�//////////
	for (int i = 0; i < 12; i++)
	{
		Sprite sprite;

		readBmpRect("asset/��.bmp", i*(53 + 2), 0, 53, 40, &sprite);

		/////////////�浹ü �߰��ϱ�///////////
		sprite.addCollider(new AABB(10, 5, 43, 35, 0), px, py);

		/////////////�ִϸ��̼� �߰�//////////
		addFrame(sprite, 0);
	}

	////////////���� �ʱ� HP ////////////////
	hp = 50;
}

void Snake::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	GameObjectPool * pool = GameObjectPool::instance();

	////////�󼾰ǰ� �浹 üũ�ϱ�///////////
	if (obj->getTag() == 0 && strcmp( obj->getName(), "�󼾰�") ==0)
	{
		hp = hp - 20;

		////////////////Flying ���̺� �����//////////////////////
		pool->addGameObject(new FlyingLabel(L"ü��: -20", 0x00ff0000, px, py), 3);

		if (hp < 0)
		{
			////////////////�� �����ϱ�-�ڽĿ�����Ʈ ����//////////////
			parentObj->delChildObj(this);  //parnetObj�� ���, this�� ��

			//////////////�� ���� �ִϸ��̼�-����� �ڽ����� �߰�///////
			parentObj->addChildObj(new SnakeDeath(getXFromParent(), getYFromParent(), makeItem), 2);

			/////////���� �ø���-Flying ���̺� �����///////////
			GameManager * manager = GameManager::instance();

			pool->addGameObject(new FlyingLabel(L"����: +10", 0x0000ff00, px + 10, py + 30), 3);
			manager->addScore(10);
		}
	}
}