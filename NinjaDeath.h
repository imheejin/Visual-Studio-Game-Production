#pragma once

#include "Animation.h"

class NinjaDeath : public Animation
{
private:

	//////////������ ���� ����///////
	bool makeItem;

public:

	NinjaDeath(float px, float py, bool makeItem);
	~NinjaDeath();

	void init();

	////////�ִϸ��̼� �����ȯ �̺�Ʈ �������̵�////
	void OnFrameChange(int id, int frame);
};