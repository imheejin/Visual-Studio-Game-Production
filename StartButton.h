#pragma once

#include "Button.h"

class StartButton : public Button
{
private:

public:
	StartButton(float px, float py);
	~StartButton();

	////////OnClick �̺�Ʈ �������̵�///////
	void OnClick();
};