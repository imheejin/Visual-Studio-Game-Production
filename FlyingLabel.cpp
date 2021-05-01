#include "stdafx.h"
#include "FlyingLabel.h"
#include "timer.h"
#include "GameObjectPool.h"

FlyingLabel::FlyingLabel(const WCHAR * text, unsigned int color, float px, float py)
			:Label(text,"asset/ttf/godoMaum.ttf", 24, color, px, py)
{
}

FlyingLabel::~FlyingLabel()
{
}

void FlyingLabel::init()
{
	////////�̵��ӵ� �ʱ�ȭ/////////
	speed = 150;

	////////������ Ÿ�� �ʱ�ȭ//////
	lifeTime = 0.5f; 
}

void FlyingLabel::update()
{
	////////////�̵���Ű��///////////
	float dist = speed * getDelteTime();
	translate(0, -dist);

	////////������Ÿ�� ����//////////
	lifeTime = lifeTime - getDelteTime();

	if (lifeTime <= 0)
	{
		GameObjectPool * pool = GameObjectPool::instance();
		pool->delGameObject(this);
	}
}