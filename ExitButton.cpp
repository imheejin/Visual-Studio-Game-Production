#include "stdafx.h"
#include "ExitButton.h"
#include "FrameWork.h"

ExitButton::ExitButton(float px, float py) : Button(L"종료", px, py)
{
}

ExitButton::~ExitButton()
{
}

void ExitButton::OnClick()
{
	/////////게임 종료 확인 절차///////
	if (MessageBox(NULL, L"정말 게임을 종료합니까?", L"게임종료", MB_YESNO) == IDYES)
	{
		/////////게임 종료////////////////
		FrameWork::instance()->ApplicationQuit();
	}
}