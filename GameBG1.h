#pragma once

#include "SpriteObject.h"

class GameBG1 : public SpriteObject
{
private:

public:
	GameBG1(float px, float py);
	~GameBG1();

	/////////�������̵� �޼ҵ�////////
	void init();
	void update();
};