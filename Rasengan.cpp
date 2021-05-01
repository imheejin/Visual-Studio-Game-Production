#include "stdafx.h"
#include "Rasengan.h"
#include "timer.h"
#include "GameObjectPool.h"
#include "Sound.h"

Rasengan::Rasengan(float px, float py) : Animation("�󼾰�", 0, true, px, py)
{
}

Rasengan::~Rasengan()
{
}

void Rasengan::init()
{
	//////////�ִϸ��̼� �ε�///////////
	for (int i = 0; i < 3; i++)
	{
		Sprite sprite;

		readBmpRect("asset/�󼾰�2.bmp", i*(107 + 2), 0, 107, 68, &sprite);

		/////////////��������Ʈ�� �浹ü �߰��ϱ�//////////
		sprite.addCollider(new AABB(35, 15, 62, 53, 0), px, py);

		addFrame(sprite, 0);
	}

	//////////�̵��ӵ� �ʱ�ȭ//////////
	speed = 150;

	//////////�̵��Ÿ� �������� �ʱ�ȭ//////
	moveDist=0;

	////////////ȿ���� �߰��ϱ�////////////
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

	////////////�� �̵��Ÿ� �����ϱ�////////
	moveDist = moveDist + dist;

	if (moveDist >= 250)
	{
		GameObjectPool * pool = GameObjectPool::instance();
		pool->delGameObject(this);
	}
}

void Rasengan::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	if (obj->getTag() == 1 && otherCol->getId()==0)  //���� 0 ���浹ü�϶�..���ظ� ��
	{
		//[1] Ǯ ��ü ��������
		GameObjectPool * pool = GameObjectPool::instance();

		//[2] Ǯ�� �ִ� �ڽ� ��ü(this)�� ������
		pool->delGameObject(this);  //�󼾰�		
	}
}