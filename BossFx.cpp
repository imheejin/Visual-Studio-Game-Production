#include "stdafx.h"
#include "BossFx.h"
#include "GameObjectPool.h"

BossFx::BossFx(float px, float py) : Animation("보스효과", 2, true, px, py)
{
}

BossFx::~BossFx()
{
}

void BossFx::init()
{
	Sprite sprite;

	/////////첫번째 이미지//////
	readBmpRect("asset/boss.bmp", 34, 1581, 32, 84, &sprite);
	addFrame(sprite, 0);

	/////////두번째 이미지//////
	readBmpRect("asset/boss.bmp", 0, 1581, 32, 84, &sprite);
	addFrame(sprite, 0);

	/////////애니메이션 속도 조절/////
	setFrameDelay(0.2);
}

void BossFx::OnFrameChange(int id, int frameNum)
{
	if (frameNum == 0)  //애님메이션 1회 완료
	{
		GameObjectPool::instance()->delGameObject(this);
	}
}