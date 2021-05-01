#include "stdafx.h"
#include <stdio.h>
#include "bmp.h"
#include "graphic.h"

int readBmp(const char *fileName, Sprite *sprite)
{
	//[1]���Ͽ��� - ���̳ʸ����� �б�� ����
	FILE *stream;
	errno_t errno;

	errno = fopen_s(&stream, fileName, "rb");

	if (errno != 0)
	{
		printf("���� ���� ����\n");
		return -1;
	}

	//[2]��Ʈ�� �����б� - �������� �б�
	MyBITMAPFILEHEADER bmpHeader;

	fread(&bmpHeader, sizeof(bmpHeader), 1, stream);

	///////////////////bmp ���� ���� ����� ����///////////////////
	printf("bfType    %x\n", bmpHeader.bfType);
	printf("bfSize    %d\n", bmpHeader.bfSize);
	printf("bfOffBits %d\n", bmpHeader.bfOffBits);

	if (bmpHeader.bfType != 0x4d42)  //�ùٸ� bitmap ������ �ƴ�
	{
		printf("bitmap ������ �ƴ�\n");
		return -1;
	}

	//[3]��Ʈ�� ���� �б� - �̹��� ���� �б�
	MyBITMAPINFOHEADER bmpInfo;

	fread(&bmpInfo, sizeof(bmpInfo), 1, stream);

	printf("�̹��� ���� ũ�� %d\n", bmpInfo.biWidth);
	printf("�̹��� ���� ũ�� %d\n", bmpInfo.biHeight);
	printf("�̹��� ��Ʈ ī��Ʈ %d\n", bmpInfo.biBitCount);

	if (bmpInfo.biBitCount != 32)  //32��Ʈ ���� - ARGB ������ �̹�����..�̿�
	{
		printf("��Ʈ�� ���Ͽ�..����(���İ�)�� ����\n");
		return -1;
	}

	//[4]��Ʈ�� ���� �б� - �̹��� ����Ÿ �б�
	sprite->width = bmpInfo.biWidth;   //�̹��� ���� ũ��
	sprite->height = bmpInfo.biHeight;  //�̹��� ���� ũ��

	/////�̹��� ���� �ʿ������ width * height * 4 ����Ʈ�� ������ �ʿ���
	sprite->argb = new unsigned int[sprite->width * sprite->height]; //�̹��� ����Ÿ ���� ���� �Ҵ�

	/////��Ŀ ����Ʈ �⺻ ����//////
	sprite->ax = 0;
	sprite->ay = 0;

	fread(sprite->argb, sizeof(sprite->argb[0]), sprite->width*sprite->height, stream);

	//���� �ݱ�
	fclose(stream);

	return 0;  //��Ʈ�� ���� �бⰡ..������
}

int readBmpRect(const char *fileName, int x, int y, int width, int height, Sprite*sprite)
{
	//[1]���Ͽ���
	FILE *stream;
	errno_t errno;

	errno = fopen_s(&stream, fileName, "rb");

	if (errno != 0)
	{
		printf("���� ���� ����\n");
		return -1;
	}

	//[2]���� ��� �о����
	MyBITMAPFILEHEADER bmpHeader;	
	fread(&bmpHeader, 1, sizeof(bmpHeader), stream);
	
	if (bmpHeader.bfType != 0x4d42)
	{
		printf("�ùٸ� BMP ������ �ƴ�\n");
		return -1;
	}
	
	//[3]bmp �̹��� �����о����
	MyBITMAPINFOHEADER bmpInfo;
	fread(&bmpInfo, 1, sizeof(bmpInfo), stream);

	//printf("��Ʈ�� ��Ʈī��Ʈ : %d\n", bmpInfo.biBitCount);
	//printf("�̹��� ���� ũ��  : %d\n", bmpInfo.biWidth);
	//printf("�̹��� ���� ũ��  : %d\n", bmpInfo.biHeight);
	if (bmpInfo.biBitCount != 32)
	{
		printf("32��Ʈ ������ �̹����� �ƴ�\n");
		return -1;
	}

	//[4]�̹��� �о����
	int bmpWidth  = bmpInfo.biWidth;   //�̹��� ��ü ���� ũ������
	int bmpHeight = bmpInfo.biHeight;  //�̹��� ��ü ���� ũ������

	//(1)�׸���ġ��..�̵��ϱ� - fseek
	int offset = (bmpWidth*y + x) * 4;
	fseek(stream, offset, SEEK_CUR);

	//(2)�̹��� �ε� �޸� �Ҵ��ϱ�
	unsigned int *argb = new unsigned int[width*height];

	//(3)�̹��� �о����
	int skip = (bmpWidth - width) * 4;

	for (int i = 0; i < height; i++)
	{
		fread(&argb[i*width], 4, width, stream);
		fseek(stream, skip, SEEK_CUR);  //������ ..�ٷ�..�̵���
	}

	//(4)�ε�� ..�̹���..��ȯ�ϱ�
	sprite->width  = width;
	sprite->height = height;
	sprite->argb   = argb;
	/////��Ŀ ����Ʈ �⺻ ����//////
	sprite->ax	  = 0;
	sprite->ay	  = 0;

	//[5] ���� �ݱ�
	fclose(stream);

	return 0;
}

void drawBmp(float px, float py, Sprite *sprite)
{
	////////////�̹��� ��Ŀ ����Ʈ//////////
	int ax = sprite->ax;
	int ay = sprite->ay;

	///////////�̹��� ����ϱ�////////////
	for (int y = 0; y < sprite->height; y++)
	{
		for (int x = 0; x < sprite->width; x++)
		{
			//x,y ��ġ��..�ȼ��� �����
			unsigned int pixel = sprite->argb[y*sprite->width + x];
			setPixel(px + x - ax , py + y - ay, pixel);
		}
	}
}

void drawBmpHFlip(float px, float py, Sprite *sprite)
{
	////////////�̹��� ��Ŀ ����Ʈ//////////
	int ax = sprite->ax;
	int ay = sprite->ay;

	///////////�̹��� ����ϱ�////////////
	for (int y = 0; y < sprite->height; y++)
	{
		for (int x = 0; x < sprite->width; x++)
		{
			//x,y ��ġ��..�ȼ��� �����
			unsigned int pixel = sprite->argb[y*sprite->width + x];
			setPixel(px + (sprite->width-1-x) - ax, py + y - ay, pixel);
		}
	}
}

///////////////////////class Sprite ������/�Ҹ���////////////////////
Sprite::Sprite()
{
	this->ax = 0;
	this->ay = 0;

	this->height = 0;
	this->width  = 0;
	this->argb   = NULL;
}

Sprite::~Sprite()
{	
}

///////////////////////class Sprite �޼ҵ�///////////////////////////
void Sprite::addCollider(AABB * aabb,  float px, float py)
{
	aabb->setOwnerPos(px, py);
	cols.push_back(aabb);
}

void Sprite::draw()
{
	///////�浹ü ����ϱ�///////
	for (int i = 0; i < cols.size(); i++)
	{
		cols[i]->draw();
	}
}