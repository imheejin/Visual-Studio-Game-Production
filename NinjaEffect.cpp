#include "stdafx.h"
#include "NinjaEffect.h"
#include "Ninja.h"

NinjaEffect::NinjaEffect(float px, float py, bool makeItem) : Animation("닌자효과", 1, true, px, py)
{
	this->makeItem = makeItem;
}

NinjaEffect::~NinjaEffect()
{
}

void NinjaEffect::init()
{
	/////////애니메이션 로드하기////////
	for (int i = 0; i < 7; i++)
	{
		Sprite sprite;

		readBmpRect("asset/닌자효과.bmp",i*(32+2), 1, 32, 56, &sprite);
		addFrame(sprite, 0);
	}
}

void NinjaEffect::OnFrameChange(int id, int frame)
{
	//////////1번 프레임에서..닌자 생성////////////
	if (frame == 1)
	{
		parentObj->addChildObj(new Ninja(getXFromParent(), getYFromParent(), makeItem), 2);
	}

	///////애니메이션 플레이 종료...효과 제거//////
	if (frame == 0)
	{
		parentObj->delChildObj(this);
	}
}