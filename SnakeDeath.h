#pragma once

#include "Animation.h"

class SnakeDeath : public Animation
{
private:

	////////������ ���� ����////////
	bool makeItem;

public:

	SnakeDeath(float px, float py, bool makeItem);
	~SnakeDeath();

	void init();
	void update();
};