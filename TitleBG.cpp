#include "stdafx.h"
#include "TitleBG.h"
#include "input.h"
#include "FrameWork.h"
#include "GameScene.h"

TitleBG::TitleBG(float px, float py) : SpriteObject("���", 2, true, px, py)
{
}

TitleBG::~TitleBG()
{
}

void TitleBG::init()
{
	////////�̹��� �ε�///////////
	readBmp("asset/Ÿ��Ʋ.bmp", &sprite);
}

void TitleBG::update()
{
}