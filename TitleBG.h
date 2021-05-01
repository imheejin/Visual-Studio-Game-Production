#pragma once

#include "SpriteObject.h"

class TitleBG : public SpriteObject
{
private:

public:

	TitleBG(float px, float py);
	~TitleBG();

	void init();
	void update();
};
