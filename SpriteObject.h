#pragma once

#include "GameObject.h"
#include "bmp.h"

class SpriteObject : public GameObject
{
protected:
	////////�����̹��� - ��������Ʈ////////
	Sprite sprite;

public:
	/////////������, �Ҹ���////////////
	SpriteObject(const char *name, int tag, bool state, float px, float py);
	~SpriteObject();

	////�̹��� ��� �޼ҵ� �������̵�////
	void draw();
};