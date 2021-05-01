#pragma once

#include <vector>
#include "GameObject.h"
#include "bmp.h"

#define MAX_ANI 64  //최대 애니메이션 갯수

class Animation : public GameObject
{
protected:

	std::vector<Sprite> frame[64];

	////////출력할 frame 번호////////
	int frameNum;

	///////출력할 애니메이션 id//////
	int aniId;

	////////애니메이션 시간//////////
	float frameDelay;  //한 장면이 보여지는 시간
	float frameTimer;  //애니메이션 타이머

	////////스프라이트 플립 결정 변수////////
	bool hFlip;  //true-HFlip, false - 플립 안함

public:

	Animation(const char *name, int tag, bool state, float px, float py);
	~Animation();

	////////애니메이션 프레임 추가 함수/////////
	void addFrame(Sprite sprite, int id);

	/////////////애니메이션 출력하기////////////
	void draw();

	//////////////애니메이션 시간 설정//////////
	void setFrameDelay(float delay);

	//////////////애니메이션 변경하기///////////
	void play(int id);

	//////충돌체 가져오기 함수 오버라이딩//////
	std::vector<AABB *> * getCols();

	//////Translate 오버라이딩///////////////
	void translate(float dx, float dy);

	//////현재 출력중인 스트라이트 번호 반환 함수//////
	int getFrameNum();

	/////애니메이션 장면이 변경되었음을 알려주는 이벤트/////
	virtual void OnFrameChange(int id, int frameNum);
};