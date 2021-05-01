#pragma once

#include "Animation.h"

class Ninja : public Animation
{
	////////////애니메이션 상태////////////////
	enum State {idle=0, attack=1, hit=2};

private:

	///////////아이템 생성여부//////////
	bool makeItem;

	State state;   //애니메이션 상태
	int    hp;     //닌자 체력 변수

public:
	Ninja(float px, float py, bool makeItem);
	~Ninja();

	void init();
	void update();

	////////충돌 이벤트 오버라이딩/////
	void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);  //충돌시작
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);       //충돌중
	void OnCollisionExit(GameObject *obj, AABB * otherCol, AABB * myCol);   //충돌끝

	////////애니메이션 장면전환 이벤트 오버라이딩////
	void OnFrameChange(int id, int frame);

	////////애니메이션 테스트 함수///////
	void aniTest();
};
