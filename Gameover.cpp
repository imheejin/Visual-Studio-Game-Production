#include "stdafx.h"
#include "Gameover.h"

Gameover::Gameover(float px, float py) :SpriteObject("���ӿ���", 2, true, px, py)
{
}

Gameover::~Gameover()
{
}

void Gameover::init()
{
	readBmp("asset/Gameover.bmp", &sprite);
}
