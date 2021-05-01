#include "stdafx.h"
#include "ESpawner.h"
#include "NinjaEffect.h"

ESpawner::ESpawner(float px, float py) : GameObject("��������ü", 1, true, px, py)
{
}

ESpawner::~ESpawner()
{
}

void ESpawner::init()
{
	////////���� ���� ��ġ �ʱ�ȭ//////////////////
	ninjaPx[0] = 450;
	ninjaPy[0] = 90;

	ninjaPx[1] = 1900;
	ninjaPy[1] = 120;

	ninjaPx[2] = 2800;
	ninjaPy[2] = 120;

	//////������ ���� ���� �迭 �ʱ�ȭ ///////////
	makeItem[0] = false;
	makeItem[1] = false;
	makeItem[2] = true;

	///////���ڸ� ������ ���� �浹ü �߰��ϱ�//////
	addCollider(new AABB(ninjaPx[0] -250, ninjaPy[0] -40, 20, 90, 0));
	addCollider(new AABB(ninjaPx[1] -250, ninjaPy[1] -40, 20, 90, 1));
	addCollider(new AABB(ninjaPx[2] -250, ninjaPy[2] -40, 20, 90, 2));
}

void ESpawner::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	if (strcmp(obj->getName(), "������") == 0 && myCol->getId() == 0)
	{
		//[1]���� ȿ�� ��ü �߰��ϱ� - ��水ü�� �߰���
		parentObj->addChildObj(new NinjaEffect(ninjaPx[0], ninjaPy[0], makeItem[0]), 3);  //��ü ������ ����

		//[2]�浹ü�� ������
		delCollider(0);
	}

	if (strcmp(obj->getName(), "������") == 0 && myCol->getId() == 1)
	{
		//[1]���� ȿ�� ��ü �߰��ϱ� - ��水ü�� �߰���
		parentObj->addChildObj(new NinjaEffect(ninjaPx[1], ninjaPy[1], makeItem[1]), 3); //��ü ������ ����

		//[2]�浹ü�� ������
		delCollider(1);
	}

	if (strcmp(obj->getName(), "������") == 0 && myCol->getId() == 2)
	{
		//[1]���� ȿ�� ��ü �߰��ϱ� - ��水ü�� �߰���
		parentObj->addChildObj(new NinjaEffect(ninjaPx[2], ninjaPy[2], makeItem[2]), 3); //��ü ������ ����

		//[2]�浹ü�� ������
		delCollider(2);
	}
}