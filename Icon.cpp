#include "stdafx.h"
#include "Icon.h"

Icon::Icon(float px, float py) : SpriteObject("������", 6, true, px, py)
{
}

Icon::~Icon()
{
}

void Icon::init()
{
	///////////�̹��� �ε��ϱ�////////
	readBmp("asset/icon.bmp", &sprite);
}
