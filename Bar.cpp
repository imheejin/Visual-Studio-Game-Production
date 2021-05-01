#include "stdafx.h"
#include "Bar.h"
#include "graphic.h"

Bar::Bar(float px, float py, float width, float height)
	:GameObject("Bar", 2, true, px, py)
{
	this->width  = width;
	this->height = height;

	////////기본 색상///////
	this->borderCol = 0x00000000; 

	/////////Bar의 기본 위치///
	this->pos    = width;
	this->barCol = 0x0000ff00;
}

Bar::~Bar()
{}

//////init 오버라이딩/////
void Bar::init()
{
	readBmp("asset/bar.bmp", &image);
}

////////draw 오버라이딩/////////
void Bar::draw()
{
	unsigned char r, g, b;
	int x0, y0, x1, y1;

	////////Bar 그리기////////////
	r = (barCol >> 16) & 0xff;
	g = (barCol >> 8) & 0xff;
	b = (barCol >> 0) & 0xff;

	x0 = px+2;
	y0 = py+3;
	x1 = px + pos-4;
	y1 = py + height-4;

	//////...내부가 채워진 사각형 그리기...//////
	for (int y = y0; y < y1; y++)
	{
		for (int x = x0; x < x1; x++)
		{
			setPixel(x, y, r, g, b);
		}
	}

	////////Bar 경계선 그리기//////
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

void Bar::setPosition(float p)  //p는 0~1사이의 비율
{
	pos = (int)(p * width);
}