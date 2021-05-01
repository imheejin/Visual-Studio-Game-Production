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
	////////////스프라이트 이미지 저장 삭제////////
	if (sprite.argb != NULL)
	{
		delete[] sprite.argb;
		sprite.argb = NULL;
	}

	/////////스프라이트 충돌체 삭제 하기/////////////
	for (int i = 0; i < sprite.cols.size(); i++)
	{
		delete sprite.cols[i];  //i 번째 충돌체 삭제
	}
		sprite.cols.clear();
}

void SpriteObject::draw()
{
	if (sprite.width != 0 && sprite.height != 0 && sprite.argb != NULL)
	{
		drawBmp(px, py, &sprite);
	}

	/////부모 클래스의 함수 실행하기//////
	GameObject::draw();
}