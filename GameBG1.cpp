#include "stdafx.h"
#include "GameBG1.h"
#include "input.h"
#include "FrameWork.h"
#include "TitleScene.h"

GameBG1::GameBG1(float px, float py):SpriteObject("���1", 2, true, px, py)
{
}

GameBG1::~GameBG1()
{
}

void GameBG1::init()
{
	readBmp("asset/���1.bmp", &sprite);
}

void GameBG1::update()
{
	if (getKeyDown(VK_ESCAPE) == true)
	{
		FrameWork::instance()->LoadScene( new TitleScene() );
	}
}