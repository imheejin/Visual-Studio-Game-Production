#pragma once

#include "Button.h"

class ExitButton : public Button
{
private:
public:
	ExitButton(float px, float py);
	~ExitButton();

	////////OnClick �̺�Ʈ �������̵�///////
	void OnClick();
};