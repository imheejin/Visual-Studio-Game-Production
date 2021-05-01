#include "stdafx.h"
#include "SnakeDeath.h"
#include "GameObjectPool.h"
#include "HPItem.h"

SnakeDeath::SnakeDeath(float px, float py, bool makeItem) : Animation("������", 1, true, px, py)
{
	this->makeItem = makeItem;
}

SnakeDeath::~SnakeDeath()
{
}

void SnakeDeath::init()
{
    ////////�ִϸ��̼� �ε�////////
	for (int i = 0; i < 7; i++)
	{
		Sprite sprite;

		readBmpRect("asset/��.bmp", i*(63 + 2), 235, 63, 51, &sprite);
		
		addFrame(sprite, 0);
	}
}

void SnakeDeath::update()
{
	if (getFrameNum() == 6)
	{
		///////////�� ���� ��ü���� - �ڽİ�ü �����ϱ�////////
		parentObj->delChildObj(this);  //parentObj�� ���, this�� �� ������ü

		/////////������ �����ϱ�///////
		if (makeItem == true)
		{
			parentObj->addChildObj(new HPItem(getXFromParent(), getYFromParent()), 2);
		}
	}
}

