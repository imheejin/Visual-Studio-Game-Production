#include "stdafx.h"
#include <stdio.h>
#include "bmp.h"
#include "graphic.h"

int readBmp(const char *fileName, Sprite *sprite)
{
	//[1]파일열기 - 바이너리파일 읽기로 열기
	FILE *stream;
	errno_t errno;

	errno = fopen_s(&stream, fileName, "rb");

	if (errno != 0)
	{
		printf("파일 열기 실패\n");
		return -1;
	}

	//[2]비트맵 파일읽기 - 파일정보 읽기
	MyBITMAPFILEHEADER bmpHeader;

	fread(&bmpHeader, sizeof(bmpHeader), 1, stream);

	///////////////////bmp 파일 정보 출력해 보기///////////////////
	printf("bfType    %x\n", bmpHeader.bfType);
	printf("bfSize    %d\n", bmpHeader.bfSize);
	printf("bfOffBits %d\n", bmpHeader.bfOffBits);

	if (bmpHeader.bfType != 0x4d42)  //올바른 bitmap 파일이 아님
	{
		printf("bitmap 파일이 아님\n");
		return -1;
	}

	//[3]비트맵 파일 읽기 - 이미지 정보 읽기
	MyBITMAPINFOHEADER bmpInfo;

	fread(&bmpInfo, sizeof(bmpInfo), 1, stream);

	printf("이미지 가로 크기 %d\n", bmpInfo.biWidth);
	printf("이미지 세로 크기 %d\n", bmpInfo.biHeight);
	printf("이미지 비트 카운트 %d\n", bmpInfo.biBitCount);

	if (bmpInfo.biBitCount != 32)  //32비트 형식 - ARGB 형식의 이미지만..이용
	{
		printf("비트맵 파일에..투명값(알파값)이 없음\n");
		return -1;
	}

	//[4]비트맵 파일 읽기 - 이미지 데이타 읽기
	sprite->width = bmpInfo.biWidth;   //이미지 가로 크기
	sprite->height = bmpInfo.biHeight;  //이미지 세로 크기

	/////이미지 저장 필요공간은 width * height * 4 바이트의 공간이 필요함
	sprite->argb = new unsigned int[sprite->width * sprite->height]; //이미지 데이타 저장 공간 할당

	/////앵커 포인트 기본 설정//////
	sprite->ax = 0;
	sprite->ay = 0;

	fread(sprite->argb, sizeof(sprite->argb[0]), sprite->width*sprite->height, stream);

	//파일 닫기
	fclose(stream);

	return 0;  //비트맵 파일 읽기가..성공함
}

int readBmpRect(const char *fileName, int x, int y, int width, int height, Sprite*sprite)
{
	//[1]파일열기
	FILE *stream;
	errno_t errno;

	errno = fopen_s(&stream, fileName, "rb");

	if (errno != 0)
	{
		printf("파일 열기 실패\n");
		return -1;
	}

	//[2]파일 헤더 읽어오기
	MyBITMAPFILEHEADER bmpHeader;	
	fread(&bmpHeader, 1, sizeof(bmpHeader), stream);
	
	if (bmpHeader.bfType != 0x4d42)
	{
		printf("올바른 BMP 파일이 아님\n");
		return -1;
	}
	
	//[3]bmp 이미지 정보읽어오기
	MyBITMAPINFOHEADER bmpInfo;
	fread(&bmpInfo, 1, sizeof(bmpInfo), stream);

	//printf("비트맵 비트카운트 : %d\n", bmpInfo.biBitCount);
	//printf("이미지 가로 크기  : %d\n", bmpInfo.biWidth);
	//printf("이미지 세로 크기  : %d\n", bmpInfo.biHeight);
	if (bmpInfo.biBitCount != 32)
	{
		printf("32비트 형식의 이미지가 아님\n");
		return -1;
	}

	//[4]이미지 읽어오기
	int bmpWidth  = bmpInfo.biWidth;   //이미지 전체 가로 크기저장
	int bmpHeight = bmpInfo.biHeight;  //이미지 전체 세로 크기저장

	//(1)그림위치로..이동하기 - fseek
	int offset = (bmpWidth*y + x) * 4;
	fseek(stream, offset, SEEK_CUR);

	//(2)이미지 로드 메모리 할당하기
	unsigned int *argb = new unsigned int[width*height];

	//(3)이미지 읽어오기
	int skip = (bmpWidth - width) * 4;

	for (int i = 0; i < height; i++)
	{
		fread(&argb[i*width], 4, width, stream);
		fseek(stream, skip, SEEK_CUR);  //다음번 ..줄로..이동함
	}

	//(4)로드된 ..이미지..반환하기
	sprite->width  = width;
	sprite->height = height;
	sprite->argb   = argb;
	/////앵커 포인트 기본 설정//////
	sprite->ax	  = 0;
	sprite->ay	  = 0;

	//[5] 파일 닫기
	fclose(stream);

	return 0;
}

void drawBmp(float px, float py, Sprite *sprite)
{
	////////////이미지 앵커 포인트//////////
	int ax = sprite->ax;
	int ay = sprite->ay;

	///////////이미지 출력하기////////////
	for (int y = 0; y < sprite->height; y++)
	{
		for (int x = 0; x < sprite->width; x++)
		{
			//x,y 위치에..픽셀을 출력함
			unsigned int pixel = sprite->argb[y*sprite->width + x];
			setPixel(px + x - ax , py + y - ay, pixel);
		}
	}
}

void drawBmpHFlip(float px, float py, Sprite *sprite)
{
	////////////이미지 앵커 포인트//////////
	int ax = sprite->ax;
	int ay = sprite->ay;

	///////////이미지 출력하기////////////
	for (int y = 0; y < sprite->height; y++)
	{
		for (int x = 0; x < sprite->width; x++)
		{
			//x,y 위치에..픽셀을 출력함
			unsigned int pixel = sprite->argb[y*sprite->width + x];
			setPixel(px + (sprite->width-1-x) - ax, py + y - ay, pixel);
		}
	}
}

///////////////////////class Sprite 생성자/소멸자////////////////////
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

///////////////////////class Sprite 메소드///////////////////////////
void Sprite::addCollider(AABB * aabb,  float px, float py)
{
	aabb->setOwnerPos(px, py);
	cols.push_back(aabb);
}

void Sprite::draw()
{
	///////충돌체 출력하기///////
	for (int i = 0; i < cols.size(); i++)
	{
		cols[i]->draw();
	}
}