#include "stdafx.h"
#include "NinjaEffect.h"
#include "Ninja.h"

NinjaEffect::NinjaEffect(float px, float py, bool makeItem) : Animation("����ȿ��", 1, true, px, py)
{
	this->makeItem = makeItem;
}

NinjaEffect::~NinjaEffect()
{
}

void NinjaEffect::init()
{
	/////////�ִϸ��̼� �ε��ϱ�////////
	for (int i = 0; i < 7; i++)
	{
		Sprite sprite;

		readBmpRect("asset/����ȿ��.bmp",i*(32+2), 1, 32, 56, &sprite);
		addFrame(sprite, 0);
	}
}

void NinjaEffect::OnFrameChange(int id, int frame)
{
	//////////1�� �����ӿ���..���� ����////////////
	if (frame == 1)
	{
		parentObj->addChildObj(new Ninja(getXFromParent(), getYFromParent(), makeItem), 2);
	}

	///////�ִϸ��̼� �÷��� ����...ȿ�� ����//////
	if (frame == 0)
	{
		parentObj->delChildObj(this);
	}
}