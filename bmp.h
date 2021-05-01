#pragma once

#include <vector>
#include "AABB.h"

#pragma pack(push, 1)   //구조체의 변수들을 ... 1 바이트씩 붙여라!!

/////////////bmp 파일 정보 구조체////////////
struct MyBITMAPFILEHEADER
{
	unsigned short bfType;		 //비트맵 파일이 정말 맞는지는 확인하는 내부 코드
	unsigned int   bfSize;		 //비트맵 파일의 크기 
	unsigned short bfReserved1;  //장래에..사용을 위한 예약 
	unsigned short bfReserved2;  //장래에..사용을 위한 예약
	unsigned int   bfOffBits;    //파일처음에서..그림 데이타가 있는 위치
};

//////////bmp 그림(이미지)정보 구조체///////////
struct MyBITMAPINFOHEADER
{
	unsigned int   biSize;           // 현재 구조체의 크기
	int            biWidth;          // 비트맵 이미지의 가로 크기
	int            biHeight;         // 비트맵 이미지의 세로 크기
	unsigned short biPlanes;         // 사용하는 색상판의 수
	unsigned short biBitCount;       // 픽셀 하나를 표현하는 비트 수
	unsigned int   biCompression;    // 압축 방식
	unsigned int   biSizeImage;      // 비트맵 이미지의 픽셀 데이터 크기
	int            biXPelsPerMeter;  // 그림의 가로 해상도(미터당 픽셀)
	int            biYPelsPerMeter;  // 그림의 세로 해상도(미터당 픽셀)
	unsigned int   biClrUsed;        // 색상 테이블에서 실제 사용되는 색상 수
	unsigned int   biClrImportant;   // 비트맵을 표현하기 위해 필요한 색상 인덱스 수
};

#pragma pack(pop)    //pack 설정을 꺼내라!!

//struct Sprite
class Sprite  
{
public:

	int width;  //스프라이트 이미지 가로 크기
	int height; //스프라이트 이미지 세로 크기

	int ax;     //스프라이트 이미지 x-앵커포인트  
	int ay;		//스프라이트 이미지 y-앵커포인트  

	////////////Sprite의 생성자 소멸자//////////
	Sprite();
	virtual ~Sprite();

	//////////Sprite에 충돌체 추가하기//////////
	std::vector<AABB *> cols;

	unsigned int * argb;  //이미지 데이터 저장 

	//////////구조체에...메소드 추가하기///////
	void addCollider(AABB * aabb, float px, float py);

	//////////충돌체 출력하기/////////////////
	void draw();



};

int readBmp(const char *fileName, Sprite *sprite);
int readBmpRect(const char *fileName, int x, int y, int width, int height, Sprite*sprite);

void drawBmp(float px, float py,  Sprite *sprite);
void drawBmpHFlip(float px, float py, Sprite *sprite);