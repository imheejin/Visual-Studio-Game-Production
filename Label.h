#pragma once

#include <Windows.h>
#include "GameObject.h"
#include "font/ft2build.h"
#include  <C:\Users\USER\Desktop\������ - �ڷ�\����\����\exec2DGame\exec2DGame\font/freetype/freetype.h>

#define MAX_LABEL 255

class Label : public GameObject
{
private:
	////////��Ʈ ���̺귯��..��� ����////
	FT_Library library;
	FT_Face face;

	////////��Ʈ ��� ��� ����///////
	WCHAR text[MAX_LABEL];
	unsigned int color;

public:
	Label(const WCHAR * text, const char * ttf, int size, unsigned int color, float px, float py);
	~Label();

	void draw();

	/////////��� �ؽ�Ʈ �����ϱ�/////////
	void setText(const WCHAR * text);
};
