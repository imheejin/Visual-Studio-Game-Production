#include "stdafx.h"
#include "ExitButton.h"
#include "FrameWork.h"

ExitButton::ExitButton(float px, float py) : Button(L"����", px, py)
{
}

ExitButton::~ExitButton()
{
}

void ExitButton::OnClick()
{
	/////////���� ���� Ȯ�� ����///////
	if (MessageBox(NULL, L"���� ������ �����մϱ�?", L"��������", MB_YESNO) == IDYES)
	{
		/////////���� ����////////////////
		FrameWork::instance()->ApplicationQuit();
	}
}