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
	////////이동속도 초기화/////////
	speed = 150;

	////////라이프 타임 초기화//////
	lifeTime = 0.5f; 
}

void FlyingLabel::update()
{
	////////////이동시키기///////////
	float dist = speed * getDelteTime();
	translate(0, -dist);

	////////라이프타임 측정//////////
	lifeTime = lifeTime - getDelteTime();

	if (lifeTime <= 0)
	{
		GameObjectPool * pool = GameObjectPool::instance();
		pool->delGameObject(this);
	}
}