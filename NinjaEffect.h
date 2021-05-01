#pragma once

#include "Animation.h"

class NinjaEffect : public Animation
{
private:

	/////////아이템 생성 여부////////
	bool makeItem;

public:

	NinjaEffect(float px, float py, bool makeItem); 
	~NinjaEffect();

	void init();

	////////애니메이션 장면전환 이벤트 오버라이딩////
	void OnFrameChange(int id, int frame);
};
