#pragma once

#include "Animation.h"

class NinjaEffect : public Animation
{
private:

	/////////������ ���� ����////////
	bool makeItem;

public:

	NinjaEffect(float px, float py, bool makeItem); 
	~NinjaEffect();

	void init();

	////////�ִϸ��̼� �����ȯ �̺�Ʈ �������̵�////
	void OnFrameChange(int id, int frame);
};
