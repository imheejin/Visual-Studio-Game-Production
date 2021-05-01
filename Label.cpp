#include "stdafx.h"
#include "Label.h"
#include "graphic.h"

Label::Label(const WCHAR * text, const char * ttf, int size, unsigned int color, float px, float py)
	  : GameObject("", 6, true, px, py)
{
	//[1]라이브러(freetype) 초기화
	if (FT_Init_FreeType(&library) != 0)
	{
		printf("폰트 라이브러리 초기화 실패\n");
	}

	//[2]ttf 폰트 파일 로드하기
	if (FT_New_Face(library, ttf , 0, &face) != 0)
	{
		printf("ttf 파일(face) 로드 실패\n");
	}

	//[3]폰트 크기 지정하기
	FT_Set_Pixel_Sizes(face, size, size);

	//[4]필요한 정보(text, color)저장하기...
	wcscpy_s(this->text, text);
	this->color = color;
}

Label::~Label()
{
	FT_Done_Face(face);         //ttf 파일을 닫음
	FT_Done_FreeType(library);  //freeType 사용이 끝남
}

void Label::draw()
{
	////폰트 출력 위치 변수////////
	int fx=px;
	int fy=py;

	////폰트를 화면에 출력하기/////
	int len = wcslen(text);

	for (int i = 0; i < len; i++)
	{
		//[4]문자에 대한 폰트 정보 읽어오기
		WCHAR c = text[i];

		//[4-1]문자에 대한 폰트 정보 위치 찾기
		int index = FT_Get_Char_Index(face, c);  //변수 c에 저장된 문자의 폰트 정보 위치 알아오기

		//[4-2]정보 위치에서..폰트 정보 읽어오기
		FT_Load_Glyph(face, index, FT_LOAD_DEFAULT);

		//[4-3]읽어온 폰트정보(glyph)을 화면에..출력할 수 있게 bitmap 이미지로 바꿈
		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);  //FT_RENDER_MODE_NORMAL은 8비트 bitmap으로 이미지를 만듬

		//[5]폰트 bitmap 출력하기
		unsigned char * buffer = face->glyph->bitmap.buffer;  //폰트 비트맵 정보 저장 배열
		int width = face->glyph->bitmap.width;   //폰트 비트맵 가로 크기
		int height = face->glyph->bitmap.rows;    //폰트 비트맵 세로 크기

		////////////////폰트 출력 사각형 위치 //////////////////
		int rx = fx + face->glyph->bitmap_left; //출력 사각형 x-위치 조정하기
		int ry = fy - face->glyph->bitmap_top;  //출력 사각형 y-위치 조정하기

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				unsigned char v = buffer[y*width + x];

				if (v != 0)
				{
					//////////color에 v를 이용한 알파값 적용하기//////
					unsigned int fontColor = color | (v << 24);

					setPixel(rx + x, ry + y, fontColor);
				}			
			}			
		}

		//////////다음 글자 출력을 위한 좌표 이동//////////
		fx = fx + face->glyph->advance.x / 64;  //64로 나누어야 픽셀 단위가됨
		fy = fy + face->glyph->advance.y / 64;  //64로 나누어야 픽셀 단위가됨

	}
}

void Label::setText(const WCHAR * text)
{
	wcscpy_s(this->text, text);
}