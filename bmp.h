#pragma once

#include <vector>
#include "AABB.h"

#pragma pack(push, 1)   //����ü�� �������� ... 1 ����Ʈ�� �ٿ���!!

/////////////bmp ���� ���� ����ü////////////
struct MyBITMAPFILEHEADER
{
	unsigned short bfType;		 //��Ʈ�� ������ ���� �´����� Ȯ���ϴ� ���� �ڵ�
	unsigned int   bfSize;		 //��Ʈ�� ������ ũ�� 
	unsigned short bfReserved1;  //�巡��..����� ���� ���� 
	unsigned short bfReserved2;  //�巡��..����� ���� ����
	unsigned int   bfOffBits;    //����ó������..�׸� ����Ÿ�� �ִ� ��ġ
};

//////////bmp �׸�(�̹���)���� ����ü///////////
struct MyBITMAPINFOHEADER
{
	unsigned int   biSize;           // ���� ����ü�� ũ��
	int            biWidth;          // ��Ʈ�� �̹����� ���� ũ��
	int            biHeight;         // ��Ʈ�� �̹����� ���� ũ��
	unsigned short biPlanes;         // ����ϴ� �������� ��
	unsigned short biBitCount;       // �ȼ� �ϳ��� ǥ���ϴ� ��Ʈ ��
	unsigned int   biCompression;    // ���� ���
	unsigned int   biSizeImage;      // ��Ʈ�� �̹����� �ȼ� ������ ũ��
	int            biXPelsPerMeter;  // �׸��� ���� �ػ�(���ʹ� �ȼ�)
	int            biYPelsPerMeter;  // �׸��� ���� �ػ�(���ʹ� �ȼ�)
	unsigned int   biClrUsed;        // ���� ���̺��� ���� ���Ǵ� ���� ��
	unsigned int   biClrImportant;   // ��Ʈ���� ǥ���ϱ� ���� �ʿ��� ���� �ε��� ��
};

#pragma pack(pop)    //pack ������ ������!!

//struct Sprite
class Sprite  
{
public:

	int width;  //��������Ʈ �̹��� ���� ũ��
	int height; //��������Ʈ �̹��� ���� ũ��

	int ax;     //��������Ʈ �̹��� x-��Ŀ����Ʈ  
	int ay;		//��������Ʈ �̹��� y-��Ŀ����Ʈ  

	////////////Sprite�� ������ �Ҹ���//////////
	Sprite();
	virtual ~Sprite();

	//////////Sprite�� �浹ü �߰��ϱ�//////////
	std::vector<AABB *> cols;

	unsigned int * argb;  //�̹��� ������ ���� 

	//////////����ü��...�޼ҵ� �߰��ϱ�///////
	void addCollider(AABB * aabb, float px, float py);

	//////////�浹ü ����ϱ�/////////////////
	void draw();



};

int readBmp(const char *fileName, Sprite *sprite);
int readBmpRect(const char *fileName, int x, int y, int width, int height, Sprite*sprite);

void drawBmp(float px, float py,  Sprite *sprite);
void drawBmpHFlip(float px, float py, Sprite *sprite);