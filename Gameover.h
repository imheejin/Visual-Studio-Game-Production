#pragma once

#include "SpriteObject.h"

class Gameover : public SpriteObject
{
private:

public:
	Gameover(float px, float py);
	~Gameover();

	void init();
};