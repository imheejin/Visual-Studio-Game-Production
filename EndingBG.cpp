#include "stdafx.h"
#include "EndingBG.h"

EndingBG::EndingBG(float px, float py) : SpriteObject("���", 2, true, px, py)
{
}

EndingBG::~EndingBG()
{
}

void EndingBG::init()
{
	readBmp("asset/����.bmp", &sprite);
}