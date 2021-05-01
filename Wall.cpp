#include "stdafx.h"
#include "Wall.h"
#include "timer.h"

Wall::Wall(float px, float py) : SpriteObject("벽", 2, true, px, py)
{
	upSpeed   = 50;
	downSpeed = 100;

	//////////////상태 초기화////////////////
	state = up;

}

Wall::Wall(float px, float py, float upSpeed, float downSpeed, State state) : SpriteObject("벽", 2, true, px, py)
{
	this->upSpeed   = upSpeed;
	this->downSpeed = downSpeed;
	this->state     = state;
}

Wall::~Wall()
{
}

void Wall::init()
{
	////////////이미지 로드하기///////////////
	readBmp("asset/벽2.bmp", &sprite);

	/////////////충돌체 추가하기//////////////
	addCollider(new AABB(30, 0, 40, 100,  0));

	/////////////이동속도/////////////////////
	//upSpeed   = 50;
	//downSpeed = 100;

	//////////////상태 초기화////////////////
	//state = up;
}

void Wall::update()
{
	if (state == up)
	{
		float dist = upSpeed * getDelteTime();
		translate(0, -dist);

		if (py <= -40)
		{
			state = down;
		}
	}
	else if (state == down) {

		float dist = downSpeed * getDelteTime();
		translate(0, dist);

		if (py >= 70)
		{
			state = up;
		}
	}
}

void Wall::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	if (strcmp(obj->getName(), "나루토") == 0)
	{
		///////////////플레이어 바운딩 박스 가져오기//////////
		float x0, y0, x1, y1;
		otherCol->getBB(x0, y0, x1, y1);

		///////////////스톤의 바운딩 박스 가져오기////////////
		float a0, b0, a1, b1;
		myCol->getBB(a0, b0, a1, b1);

		//////////////바운딩 박스 중심 구하기////////////////
		//[플레이어 중심]
		float pcx = (x0 + x1) / 2;
		float pcy = (y0 + y1) / 2;

		//[스톤의 중심]
		float scx = (a0 + a1) / 2;
		float scy = (b0 + b1) / 2;

		//[플레이어 점프...기능 추가시..수정 필요]
		if (pcx < scx)
		{
			float w = x1 - a0;
			obj->translate(-w, 0);
		}
		else {

			float w = a1 - x0;
			obj->translate(w, 0);
		}
	}
}