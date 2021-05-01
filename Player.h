#pragma once

#include "Animation.h"

class Player : public Animation
{
private:
	
	////////////////////애니메이션 상태//////////////////
	enum State { run = 0, jump = 1, attack = 2, hit=3 };

	////////이동 속도/////////
	float runSpeed;  //run 이동속도
	float jumpSpeed; //jump 이동속도

	/////애니메이션 상태/////
	State state;

	//////체력 변수 추가하기//////
	//int hp;

public:
	Player(float px, float py);
	~Player();

	////////플레이어 초기화/////////
	void init();

	/////////플레이어 업데이트///////
	void update();

	////////충돌 이벤트 오버라이딩/////
	void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);

	////////애니메이션 테스트 함수/////
	void AniTest();
};