#pragma once

#include "Animation.h"

class BossFx : public Animation
{
private:

public:
	BossFx(float px, float py);
	~BossFx();

	void init();

	//////////�ִϸ��̼� �����̺�Ʈ///////////
	void OnFrameChange(int id, int frameNum);

};