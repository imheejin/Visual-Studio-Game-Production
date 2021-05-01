#pragma once

#include "Animation.h"

class PlayerDeath : public Animation
{
private:

public:

	PlayerDeath(float px, float py);
	~PlayerDeath();

	void init();

	////////애니메이션 장면전환 이벤트 오버라이딩////
	void OnFrameChange(int id, int frame);
};
