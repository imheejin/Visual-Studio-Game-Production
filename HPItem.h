#pragma once

#include "SpriteObject.h"

class HPItem : public SpriteObject
{
	private:

		////////������ �ð� ����/////////
		float lifeTime;

	public:
		HPItem(float px, float py);
		~HPItem();

		void init();
		void update();

		////////�浹 �̺�Ʈ �������̵�/////
		void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);
};
