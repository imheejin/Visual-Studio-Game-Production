#pragma once

#include "Label.h"

class FlyingLabel : public Label
{
private:

	/////////이동속도/////////
	float speed;

	////////라이프 타임///////
	float lifeTime;

public:
	FlyingLabel(const WCHAR * text, unsigned int color, float px, float py);
	~FlyingLabel();

	void init();
	void update();
};