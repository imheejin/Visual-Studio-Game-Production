#include "stdafx.h"
#include "HPItem.h"
#include "GameObjectPool.h"
#include "timer.h"

HPItem::HPItem(float px, float py) : SpriteObject("HPItem", 5, true, px, py)
{
}

HPItem::~HPItem()
{
}

void HPItem::init()
{
	///////////이미지 로드하기/////////
	readBmpRect("asset/item.bmp", 146, 66, 144, 64, &sprite);

	///////////충돌체 추가하기////////
	addCollider(new AABB(40, 32, 16, 16, 0));

	///////////아이템 지속시간 초기화//////
	lifeTime = 5;
}

void HPItem::update()
{
	lifeTime = lifeTime - getDelteTime();

	if (lifeTime < 0)  //아이템 지속 시간이 모두 지남
	{
		parentObj->delChildObj(this);
	}
}

void HPItem::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	if (obj->getTag() == 0 && strcmp(obj->getName(), "나루토") == 0)
	{
		parentObj->delChildObj(this);
	}
}