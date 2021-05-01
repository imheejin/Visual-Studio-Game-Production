#include "stdafx.h"
#include "Bar.h"
#include "graphic.h"

Bar::Bar(float px, float py, float width, float height)
	:GameObject("Bar", 2, true, px, py)
{
	this->width  = width;
	this->height = height;

	////////�⺻ ����///////
	this->borderCol = 0x00000000; 

	/////////Bar�� �⺻ ��ġ///
	this->pos    = width;
	this->barCol = 0x0000ff00;
}

Bar::~Bar()
{}

//////init �������̵�/////
void Bar::init()
{
	readBmp("asset/bar.bmp", &image);
}

////////draw �������̵�/////////
void Bar::draw()
{
	unsigned char r, g, b;
	int x0, y0, x1, y1;

	////////Bar �׸���////////////
	r = (barCol >> 16) & 0xff;
	g = (barCol >> 8) & 0xff;
	b = (barCol >> 0) & 0xff;

	x0 = px+2;
	y0 = py+3;
	x1 = px + pos-4;
	y1 = py + height-4;

	//////...���ΰ� ä���� �簢�� �׸���...//////
	for (int y = y0; y < y1; y++)
	{
		for (int x = x0; x < x1; x++)
		{
			setPixel(x, y, r, g, b);
		}
	}

	////////Bar ��輱 �׸���//////
	r = (borderCol >> 16) & 0xff;
	g = (borderCol >>  8) & 0xff;
	b = (borderCol >>  0) & 0xff;

	x0 = px;
	y0 = py;
	x1 = px + width;
	y1 = py + height;

	//drawRect(x0, y0, x1, y1, r, g, b);
	drawBmp(px, py, &image);
}

void Bar::setPosition(float p)  //p�� 0~1������ ����
{
	pos = (int)(p * width);
}