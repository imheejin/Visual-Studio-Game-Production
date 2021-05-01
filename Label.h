#pragma once

#include <Windows.h>
#include "GameObject.h"
#include "font/ft2build.h"
#include  <C:\Users\USER\Desktop\임희진 - 자료\수시\게임\exec2DGame\exec2DGame\font/freetype/freetype.h>

#define MAX_LABEL 255

class Label : public GameObject
{
private:
	////////폰트 라이브러리..멤버 변수////
	FT_Library library;
	FT_Face face;

	////////폰트 사용 멤버 변수///////
	WCHAR text[MAX_LABEL];
	unsigned int color;

public:
	Label(const WCHAR * text, const char * ttf, int size, unsigned int color, float px, float py);
	~Label();

	void draw();

	/////////출력 텍스트 변경하기/////////
	void setText(const WCHAR * text);
};
