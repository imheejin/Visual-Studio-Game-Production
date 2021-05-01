#include "stdafx.h"
#include "BossFx.h"
#include "GameObjectPool.h"

BossFx::BossFx(float px, float py) : Animation("����ȿ��", 2, true, px, py)
{
}

BossFx::~BossFx()
{
}

void BossFx::init()
{
	Sprite sprite;

	/////////ù��° �̹���//////
	readBmpRect("asset/boss.bmp", 34, 1581, 32, 84, &sprite);
	addFrame(sprite, 0);

	/////////�ι�° �̹���//////
	readBmpRect("asset/boss.bmp", 0, 1581, 32, 84, &sprite);
	addFrame(sprite, 0);

	/////////�ִϸ��̼� �ӵ� ����/////
	setFrameDelay(0.2);
}

void BossFx::OnFrameChange(int id, int frameNum)
{
	if (frameNum == 0)  //�ִԸ��̼� 1ȸ �Ϸ�
	{
		GameObjectPool::instance()->delGameObject(this);
	}
}