#pragma once

#include "Animation.h"

class PlayerDeath : public Animation
{
private:

public:

	PlayerDeath(float px, float py);
	~PlayerDeath();

	void init();

	////////�ִϸ��̼� �����ȯ �̺�Ʈ �������̵�////
	void OnFrameChange(int id, int frame);
};
