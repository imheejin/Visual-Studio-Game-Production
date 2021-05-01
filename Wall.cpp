#include "stdafx.h"
#include "Wall.h"
#include "timer.h"

Wall::Wall(float px, float py) : SpriteObject("��", 2, true, px, py)
{
	upSpeed   = 50;
	downSpeed = 100;

	//////////////���� �ʱ�ȭ////////////////
	state = up;

}

Wall::Wall(float px, float py, float upSpeed, float downSpeed, State state) : SpriteObject("��", 2, true, px, py)
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
	////////////�̹��� �ε��ϱ�///////////////
	readBmp("asset/��2.bmp", &sprite);

	/////////////�浹ü �߰��ϱ�//////////////
	addCollider(new AABB(30, 0, 40, 100,  0));

	/////////////�̵��ӵ�/////////////////////
	//upSpeed   = 50;
	//downSpeed = 100;

	//////////////���� �ʱ�ȭ////////////////
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
	if (strcmp(obj->getName(), "������") == 0)
	{
		///////////////�÷��̾� �ٿ�� �ڽ� ��������//////////
		float x0, y0, x1, y1;
		otherCol->getBB(x0, y0, x1, y1);

		///////////////������ �ٿ�� �ڽ� ��������////////////
		float a0, b0, a1, b1;
		myCol->getBB(a0, b0, a1, b1);

		//////////////�ٿ�� �ڽ� �߽� ���ϱ�////////////////
		//[�÷��̾� �߽�]
		float pcx = (x0 + x1) / 2;
		float pcy = (y0 + y1) / 2;

		//[������ �߽�]
		float scx = (a0 + a1) / 2;
		float scy = (b0 + b1) / 2;

		//[�÷��̾� ����...��� �߰���..���� �ʿ�]
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