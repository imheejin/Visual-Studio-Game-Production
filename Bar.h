#pragma once

#include "GameObject.h"
#include "bmp.h"

class Bar : public GameObject
{
private:

	///////바의 가로/세로 크기//////
	float width;
	float height;

	///////바의 경계선 색//////////////
	unsigned int borderCol;

	/////////바의 위치, 색/////////////////
	float pos;
	unsigned int barCol;

	////////바(bar)위에 출력할 투명 이미지//////
	Sprite image;

public:

	Bar(float px, float py, float width, float height);
	~Bar();

	////////init, draw 오버라이딩/////////
	void init();
	void draw();

	////////채워지는 bar의 길이(비율) 지정메소드//////
	void setPosition(float p);  //p는 0~1사이의 비율
};