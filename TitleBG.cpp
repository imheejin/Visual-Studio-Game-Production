#include "stdafx.h"
#include "TitleBG.h"
#include "input.h"
#include "FrameWork.h"
#include "GameScene.h"

TitleBG::TitleBG(float px, float py) : SpriteObject("배경", 2, true, px, py)
{
}

TitleBG::~TitleBG()
{
}

void TitleBG::init()
{
	////////이미지 로드///////////
	readBmp("asset/타이틀.bmp", &sprite);
}

void TitleBG::update()
{
}