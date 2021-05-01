#pragma once

#include "SpriteObject.h"

class GameBG1 : public SpriteObject
{
private:

public:
	GameBG1(float px, float py);
	~GameBG1();

	/////////오버라이딩 메소드////////
	void init();
	void update();
};