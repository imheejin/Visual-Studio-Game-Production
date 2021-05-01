#pragma once

#include "Label.h"

class FlyingLabel : public Label
{
private:

	/////////�̵��ӵ�/////////
	float speed;

	////////������ Ÿ��///////
	float lifeTime;

public:
	FlyingLabel(const WCHAR * text, unsigned int color, float px, float py);
	~FlyingLabel();

	void init();
	void update();
};