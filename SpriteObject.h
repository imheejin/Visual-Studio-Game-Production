#pragma once

#include "GameObject.h"
#include "bmp.h"

class SpriteObject : public GameObject
{
protected:
	////////게임이미지 - 스프라이트////////
	Sprite sprite;

public:
	/////////생성자, 소멸자////////////
	SpriteObject(const char *name, int tag, bool state, float px, float py);
	~SpriteObject();

	////이미지 출력 메소드 오버라이딩////
	void draw();
};