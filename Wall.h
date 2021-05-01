#pragma once

#include "SpriteObject.h"


class Wall : public SpriteObject
{
private:
	//////////////벽이동 상태 enum 만들기///////////
	enum State { up = 0, down = 1 };

	//////////이동속도/////////	
	float upSpeed;   //[1]위로 이동속도
	float downSpeed; //[2]아래로 이동 속도

	/////////상태 변수/////////
	State state;

public:
	Wall(float px, float py);
	Wall(float px, float py, float upSpeed, float downSpeed, State state);
	~Wall();

	void init();
	void update();

	/////////////////////충돌체 오버라이딩//////////////////////////
	void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);
};