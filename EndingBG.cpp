#include "stdafx.h"
#include "EndingBG.h"

EndingBG::EndingBG(float px, float py) : SpriteObject("배경", 2, true, px, py)
{
}

EndingBG::~EndingBG()
{
}

void EndingBG::init()
{
	readBmp("asset/엔딩.bmp", &sprite);
}