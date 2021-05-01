#include "stdafx.h"
#include "NinjaDeath.h"
#include "GameObjectPool.h"
#include "HPItem.h"

NinjaDeath::NinjaDeath(float px, float py, bool makeItem) : Animation("��������", 0, true, px, py)
{
	this->makeItem = makeItem;
}

NinjaDeath::~NinjaDeath()
{
}

void NinjaDeath::init()
{
    //////�ִϸ��̼� �ε��ϱ�/////
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBmpRect("asset/����.bmp", i*(59 + 2), 318, 59, 56, &sprite);
		addFrame(sprite, 0);
	}
}

void NinjaDeath::OnFrameChange(int id, int frame)
{
	if (frame == 0)
	{
		parentObj->delChildObj(this);

		/////////������ �����ϱ�///////
		if (makeItem == true)
		{
			parentObj->addChildObj(new HPItem(getXFromParent(), getYFromParent()), 2);
		}
	}
}