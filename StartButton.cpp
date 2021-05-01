#include "stdafx.h"
#include "StartButton.h"
#include "FrameWork.h"
#include "GameScene.h"

StartButton::StartButton(float px, float py) : Button(L"½ÃÀÛ", px, py)
{
}

StartButton::~StartButton()
{
	
}

void StartButton::OnClick()
{
	FrameWork::instance()->LoadScene( new GameScene() );
}