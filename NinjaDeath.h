#pragma once

#include "Animation.h"

class NinjaDeath : public Animation
{
private:

	//////////아이템 생성 여부///////
	bool makeItem;

public:

	NinjaDeath(float px, float py, bool makeItem);
	~NinjaDeath();

	void init();

	////////애니메이션 장면전환 이벤트 오버라이딩////
	void OnFrameChange(int id, int frame);
};