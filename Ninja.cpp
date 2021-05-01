#include "stdafx.h"
#include "Ninja.h"
#include "input.h"
#include "Scythe.h"
#include "GameObjectPool.h"
#include "NinjaDeath.h"
#include "FlyingLabel.h"
#include "GameManager.h"

Ninja::Ninja(float px, float py, bool makeItem) : Animation("����", 1, true, px, py)
{
	this->makeItem = makeItem;
}

Ninja::~Ninja()
{
}

void Ninja::init()
{
	//////////�ִϸ��̼� �ε��ϱ�-idle �ִϸ��̼� //////////
	for (int i = 0; i < 4; i++)
	{
		Sprite sprite;

		readBmpRect("asset/����.bmp", i*(42 + 2), 0, 42, 49, &sprite);

		/////////////////�浹ü �߰��ϱ�////////////////
		sprite.addCollider(new AABB(0, 0, 33, 49,    0), px, py); //�÷��̾� ���� ����

		sprite.addCollider(new AABB(-160, 0, 195, 49, 1), px, py); //�÷��̾� ���� ����

		addFrame(sprite, idle);
	}

	//////////�ִϸ��̼� �ε��ϱ�-attack �ִϸ��̼�//////////
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBmpRect("asset/����.bmp", i*(56 + 2), 51, 56, 48, &sprite);

		/////////��Ʈ����Ʈ ��Ŀ����Ʈ �����ϱ�///////////
		sprite.ax = 20;

		/////////////////�浹ü �߰��ϱ�////////////////
		sprite.addCollider(new AABB(-10, 5, 38, 44, 0), px, py); //�÷��̾� ���� ����

		sprite.addCollider(new AABB(-180, 5, 208, 44, 2), px, py); //�÷��̾� �־��� ����

		addFrame(sprite, attack);
	}

	///////////////�ִϸ��̼� �ε��ϱ� - hit �ִϸ��̼�////////
	for (int i = 0; i < 2; i++)
	{
		Sprite sprite;

		readBmpRect("asset/����.bmp", i*(41 + 2), 218, 41, 56, &sprite);
		addFrame(sprite, hit);    //���� ����(hit)�ִϸ��̼� �߰��ϱ�
	}

	//////////////�ִϸ��̼� ���� �ʱ�ȭ///////////
	state = idle;
	play(state);

	//////////////���� hp �ʱ�ȭ//////////////////
	hp = 100;

}

void Ninja::update()
{
}

void Ninja::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	GameObjectPool * pool = GameObjectPool::instance();

	///////�÷��̾ ���ڿ� ���� �˻� - ���ݹ����� ���Դ��� üũ/////////
	if (strcmp(obj->getName(), "������") == 0 && myCol->getId() == 1)  //������ 1 ���浹ü
	{
		state = attack;
		play(attack);
		setFrameDelay(0.25);
	}
	
	////////////////���ڰ� �󼾰ǿ�..������..hp ���� ��Ű��////////////////
	if (strcmp(obj->getName(), "�󼾰�") == 0 && myCol->getId() == 0)
	{
		/////////////////���� hit �ִϸ��̼� ��ȯ�ϱ�//////////////
		state = hit;
		play(hit);

		/////////////////���� ü�� ���ҽ�Ű��/////////////////////
		hp = hp - 50;
		
		////////////////Flying ���̺� �����//////////////////////
		pool->addGameObject(new FlyingLabel(L"ü��: -50", 0x00ff0000, px, py), 3);

		if (hp < 0)
		{
			//////////ü���� ��� �����Ǹ�..���ڸ� ������-�ڽ����� �߰��Ǹ�..�ڽİ�ü ����⸦ �ؾ���////////////
			parentObj->delChildObj(this);

			/////////���� ���� �ִϸ��̼� ��ü ����////////////
			parentObj->addChildObj(new NinjaDeath( getXFromParent(),  getYFromParent(), makeItem ), 2);  //��ũ�ѵ� �θ� ��ü�� �������� ��ǥ ����

			/////////���� �ø���-Flying ���̺� �����///////////
			GameManager * manager = GameManager::instance();

			pool->addGameObject(new FlyingLabel(L"����: +20", 0x0000ff00, px+10, py+30), 3);
			manager->addScore(20);
		}
	}
}

void Ninja::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
}

void Ninja::OnCollisionExit(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	///////////////�÷��̾ ���� ������ ��������� �˻�////////////
	if (strcmp(obj->getName(), "������") == 0 && myCol->getId() == 2)
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

	//////////hit �ִϸ��̼� ���󺹱��ϱ�//////////
	if (id == hit && frame == 0)
	{
		/////////idle �ִϸ��̼����� ������//////////
		state = idle;
		play(idle);

		setFrameDelay(0.1);  //�ִϸ��̼Ǽӵ�..����
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