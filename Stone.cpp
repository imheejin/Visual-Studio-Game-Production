#include "stdafx.h"
#include "Stone.h"

Stone::Stone(float px, float py) : SpriteObject("����", 2, true, px, py)
{
}

Stone::~Stone()
{
}

void Stone::init()
{
	////////////�̹��� �ε��ϱ�//////////////
	readBmp("asset/stone3.bmp", &sprite);

	////////////�浹ü �߰��ϱ�//////////////
	addCollider(new AABB(8, 5, 30, 40, 0));
}

void Stone::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
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