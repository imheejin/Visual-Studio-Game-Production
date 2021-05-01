#include "stdafx.h"
#include "Scythe.h"
#include "timer.h"
#include "GameObjectPool.h"

Scythe::Scythe(float px, float py) : Animation("ū��", 1, true, px, py)
{
}

Scythe::~Scythe()
{
}

void Scythe::init()
{
	////////�ִϸ��̼� �ε��ϱ�////////
	for (int i = 0; i < 4; i++)
	{
		Sprite sprite;

		readBmpRect("asset/����.bmp", i*(40 + 2), 418, 40, 40, &sprite);

		//////////////�浹ü �߰��ϱ�/////////////
		sprite.addCollider(new AABB(10, 10, 20, 20, 0), px, py);

		addFrame(sprite, 0);
	}

	//////////�ִϸ޴ϼ� �ӵ� �����ϱ�//////////
	setFrameDelay(0.05);

	//////////////�̵��ӵ� �����ϱ�/////////////
	speed = 150;

	//////////////�� �̵��Ÿ� �ʱ�ȭ �ϱ�////////
	moveDist = 0;

}

void Scythe::update()
{		
	float dist = speed * getDelteTime();
	translate(-dist, 0);

	//////////���� ���̵��Ÿ� ���ϱ�//////////
	moveDist = moveDist + dist;

	if (moveDist >= 200)
	{
		GameObjectPool * pool = GameObjectPool::instance();
		pool->delGameObject(this);
	}

}

///////////////�浹 ���� �˻��ϱ�//////////////
void Scythe::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)  
{
	if (strcmp(obj->getName(), "������") == 0)
	{
		/////////�� �����ϱ�///////
		GameObjectPool * pool = GameObjectPool::instance();
		pool->delGameObject(this);
	}
}