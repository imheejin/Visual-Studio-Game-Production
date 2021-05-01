#include "stdafx.h"
#include "GameBG2.h"
#include "timer.h"
#include "graphic.h"
#include "Stone.h"
#include "Wall.h"
#include "Snake.h"
#include "ESpawner.h"
#include "GameManager.h"

GameBG2::GameBG2(float px, float py):SpriteObject("���2", 2, true, px, py)
{
}

GameBG2::~GameBG2()
{
}

void GameBG2::init()
{
	//////////����̹��� �ε�/////////
	readBmp("asset/���2.bmp", &sprite);

	//////////��� �浹ü �߰��ϱ�//////
	addCollider(new AABB(0,   141, 608,  55, 0));
	addCollider(new AABB(609, 171, 2567, 55, 0));

	addCollider(new AABB(2977, 75, 131, 117, 1));  //���� ���� ��Ű�� �浹ü

	//////////���� �ޱ�-�ڽİ��� ������Ʈ �߰�///////
	addChildObj(new Stone(1000, 140), 2);
	addChildObj(new Stone(1570, 140), 2);
	addChildObj(new Stone(2070, 140), 2);

	//////////�����̴� �� �ޱ� - �ڽİ��� ������Ʈ �߰�/////
	addChildObj(new Wall(1370, 140), 2);
	addChildObj(new Wall(2250, 140), 2);

	//////////////////�� �߰��ϱ� //////////////////
	addChildObj(new Snake(445,  100, false), 2);	
	addChildObj(new Snake(950,  130, true), 2);
	addChildObj(new Snake(1800, 130, false), 2);
	
	/////////////////�� ������ü(Spawner) �߰��ϱ�//////
	addChildObj(new ESpawner(0, 0), 1);

	//////////////�̵��ӵ� �ʱ�ȭ///////////////////
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

	//�̹����� px �� �ּ� -(imgWidth - scrWidth)���� ���� ����

	int minPx = -(imgWidth - scrWidth);

	if (px > minPx)
	{		
		GameObject::translate(dx, dy);
	}
}

void GameBG2::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	if (strcmp(obj->getName(), "������") == 0 && myCol->getId()==0)  //�÷��̾ ���� ���� �ø�
	{
		//////////�÷��̾� �ٿ���ڽ� ��ǥ ��������/////////////////
		float x0, y0, x1, y1;
		otherCol->getBB(x0, y0, x1, y1);

		/////////����� �ٿ���ڽ� ��ǥ ��������////////////////////
		float a0, b0, a1, b1;
		myCol->getBB(a0, b0, a1, b1);

		//////////////�÷��̾� ���� �ø���/////////////////////////
		float h = y1 - b0;

		obj->translate(0, -h);

	}
	else if (strcmp(obj->getName(), "������") == 0 && myCol->getId() == 1) {

		//////////�÷��̾� �ٿ���ڽ� ��ǥ ��������/////////////////
		float x0, y0, x1, y1;
		otherCol->getBB(x0, y0, x1, y1);

		/////////����� �ٿ���ڽ� ��ǥ ��������////////////////////
		float a0, b0, a1, b1;
		myCol->getBB(a0, b0, a1, b1);

		////////////////�÷��̾� �ڷ� ������//////////////////////
		float w = x1 - a0;
		obj->translate(-w, 0);

		///////////////���� �����ϱ�//////////////////////////////
		GameManager::instance()->bossSpawn();

		//printf("���� ����\n");

		///////////////�浹ü �����ϱ�////////////////////////////
		delCollider(1);
	}
	
}