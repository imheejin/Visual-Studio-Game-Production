#pragma once

#include "Animation.h"

class BossFx : public Animation
{
private:

public:
	BossFx(float px, float py);
	~BossFx();

	void init();

	//////////애니메이션 변경이벤트///////////
	void OnFrameChange(int id, int frameNum);

};