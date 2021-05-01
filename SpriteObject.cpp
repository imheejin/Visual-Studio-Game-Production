#include "stdafx.h"
#include "SpriteObject.h"

SpriteObject::SpriteObject(const char *name, int tag, bool state, float px, float py)
	         :GameObject(name, tag, state, px, py)
{
	sprite.width  = 0;
	sprite.height = 0;
	sprite.argb   = NULL;
}

SpriteObject::~SpriteObject()
{
	////////////��������Ʈ �̹��� ���� ����////////
	if (sprite.argb != NULL)
	{
		delete[] sprite.argb;
		sprite.argb = NULL;
	}

	/////////��������Ʈ �浹ü ���� �ϱ�/////////////
	for (int i = 0; i < sprite.cols.size(); i++)
	{
		delete sprite.cols[i];  //i ��° �浹ü ����
	}
		sprite.cols.clear();
}

void SpriteObject::draw()
{
	if (sprite.width != 0 && sprite.height != 0 && sprite.argb != NULL)
	{
		drawBmp(px, py, &sprite);
	}

	/////�θ� Ŭ������ �Լ� �����ϱ�//////
	GameObject::draw();
}