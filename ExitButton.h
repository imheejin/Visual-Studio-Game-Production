#pragma once

#include "Button.h"

class ExitButton : public Button
{
private:
public:
	ExitButton(float px, float py);
	~ExitButton();

	////////OnClick 이벤트 오버라이딩///////
	void OnClick();
};