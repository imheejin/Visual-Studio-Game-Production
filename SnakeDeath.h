#pragma once

#include "Animation.h"

class SnakeDeath : public Animation
{
private:

	////////아이템 생성 여부////////
	bool makeItem;

public:

	SnakeDeath(float px, float py, bool makeItem);
	~SnakeDeath();

	void init();
	void update();
};