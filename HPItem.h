#pragma once

#include "SpriteObject.h"

class HPItem : public SpriteObject
{
	private:

		////////아이템 시간 제한/////////
		float lifeTime;

	public:
		HPItem(float px, float py);
		~HPItem();

		void init();
		void update();

		////////충돌 이벤트 오버라이딩/////
		void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol);
};
