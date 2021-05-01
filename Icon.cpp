#include "stdafx.h"
#include "Icon.h"

Icon::Icon(float px, float py) : SpriteObject("아이콘", 6, true, px, py)
{
}

Icon::~Icon()
{
}

void Icon::init()
{
	///////////이미지 로드하기////////
	readBmp("asset/icon.bmp", &sprite);
}
