#include "stdafx.h"
#include "SnakeDeath.h"
#include "GameObjectPool.h"
#include "HPItem.h"

SnakeDeath::SnakeDeath(float px, float py, bool makeItem) : Animation("πÏ¡◊¿Ω", 1, true, px, py)
{
	this->makeItem = makeItem;
}

SnakeDeath::~SnakeDeath()
{
}

void SnakeDeath::init()
{
    ////////æ÷¥œ∏ﬁ¿Ãº« ∑ŒµÂ////////
	for (int i = 0; i < 7; i++)
	{
		Sprite sprite;

		readBmpRect("asset/πÏ.bmp", i*(63 + 2), 235, 63, 51, &sprite);
		
		addFrame(sprite, 0);
	}
}

void SnakeDeath::update()
{
	if (getFrameNum() == 6)
	{
		///////////πÏ ¡◊¿Ω ∞¥√º¡¶∞≈ - ¿⁄Ωƒ∞¥√º ¡¶∞≈«œ±‚////////
		parentObj->delChildObj(this);  //parentObj¥¬ πË∞Ê, this¥¬ πÏ ¡◊¿Ω∞¥√º

		/////////æ∆¿Ã≈€ ª˝º∫«œ±‚///////
		if (makeItem == true)
		{
			parentObj->addChildObj(new HPItem(getXFromParent(), getYFromParent()), 2);
		}
	}
}

