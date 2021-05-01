#pragma once

#include "Button.h"

class StartButton : public Button
{
private:

public:
	StartButton(float px, float py);
	~StartButton();

	////////OnClick 이벤트 오버라이딩///////
	void OnClick();
};