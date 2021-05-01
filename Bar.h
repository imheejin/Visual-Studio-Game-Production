#pragma once

#include "GameObject.h"
#include "bmp.h"

class Bar : public GameObject
{
private:

	///////���� ����/���� ũ��//////
	float width;
	float height;

	///////���� ��輱 ��//////////////
	unsigned int borderCol;

	/////////���� ��ġ, ��/////////////////
	float pos;
	unsigned int barCol;

	////////��(bar)���� ����� ���� �̹���//////
	Sprite image;

public:

	Bar(float px, float py, float width, float height);
	~Bar();

	////////init, draw �������̵�/////////
	void init();
	void draw();

	////////ä������ bar�� ����(����) �����޼ҵ�//////
	void setPosition(float p);  //p�� 0~1������ ����
};