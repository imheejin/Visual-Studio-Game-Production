#pragma once

#include "Animation.h"

class Boss : public Animation
{
private:

	enum State{ walk, attack1, attack2, death};
	
	int hp;		   ///////hp 변수///////
	State state;   //보스 상태 변수

	float speed;       //보스의 이동 속도
	float attackDist;  //보스의 공격 거리

	float attack1Delay; //첫번째 공격 지속시간

public:

	Boss(float px, float py);
	~Boss();

	void init();
	void update();

	////////충돌 이벤트 오버라이딩/////
	void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);

	////////애니메이션 변경이벤트//////
	void OnFrameChange(int id, int frameNum);

	void aniTest();
};