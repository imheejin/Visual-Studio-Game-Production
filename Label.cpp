#include "stdafx.h"
#include "Label.h"
#include "graphic.h"

Label::Label(const WCHAR * text, const char * ttf, int size, unsigned int color, float px, float py)
	  : GameObject("", 6, true, px, py)
{
	//[1]���̺귯(freetype) �ʱ�ȭ
	if (FT_Init_FreeType(&library) != 0)
	{
		printf("��Ʈ ���̺귯�� �ʱ�ȭ ����\n");
	}

	//[2]ttf ��Ʈ ���� �ε��ϱ�
	if (FT_New_Face(library, ttf , 0, &face) != 0)
	{
		printf("ttf ����(face) �ε� ����\n");
	}

	//[3]��Ʈ ũ�� �����ϱ�
	FT_Set_Pixel_Sizes(face, size, size);

	//[4]�ʿ��� ����(text, color)�����ϱ�...
	wcscpy_s(this->text, text);
	this->color = color;
}

Label::~Label()
{
	FT_Done_Face(face);         //ttf ������ ����
	FT_Done_FreeType(library);  //freeType ����� ����
}

void Label::draw()
{
	////��Ʈ ��� ��ġ ����////////
	int fx=px;
	int fy=py;

	////��Ʈ�� ȭ�鿡 ����ϱ�/////
	int len = wcslen(text);

	for (int i = 0; i < len; i++)
	{
		//[4]���ڿ� ���� ��Ʈ ���� �о����
		WCHAR c = text[i];

		//[4-1]���ڿ� ���� ��Ʈ ���� ��ġ ã��
		int index = FT_Get_Char_Index(face, c);  //���� c�� ����� ������ ��Ʈ ���� ��ġ �˾ƿ���

		//[4-2]���� ��ġ����..��Ʈ ���� �о����
		FT_Load_Glyph(face, index, FT_LOAD_DEFAULT);

		//[4-3]�о�� ��Ʈ����(glyph)�� ȭ�鿡..����� �� �ְ� bitmap �̹����� �ٲ�
		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);  //FT_RENDER_MODE_NORMAL�� 8��Ʈ bitmap���� �̹����� ����

		//[5]��Ʈ bitmap ����ϱ�
		unsigned char * buffer = face->glyph->bitmap.buffer;  //��Ʈ ��Ʈ�� ���� ���� �迭
		int width = face->glyph->bitmap.width;   //��Ʈ ��Ʈ�� ���� ũ��
		int height = face->glyph->bitmap.rows;    //��Ʈ ��Ʈ�� ���� ũ��

		////////////////��Ʈ ��� �簢�� ��ġ //////////////////
		int rx = fx + face->glyph->bitmap_left; //��� �簢�� x-��ġ �����ϱ�
		int ry = fy - face->glyph->bitmap_top;  //��� �簢�� y-��ġ �����ϱ�

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				unsigned char v = buffer[y*width + x];

				if (v != 0)
				{
					//////////color�� v�� �̿��� ���İ� �����ϱ�//////
					unsigned int fontColor = color | (v << 24);

					setPixel(rx + x, ry + y, fontColor);
				}			
			}			
		}

		//////////���� ���� ����� ���� ��ǥ �̵�//////////
		fx = fx + face->glyph->advance.x / 64;  //64�� ������� �ȼ� ��������
		fy = fy + face->glyph->advance.y / 64;  //64�� ������� �ȼ� ��������

	}
}

void Label::setText(const WCHAR * text)
{
	wcscpy_s(this->text, text);
}