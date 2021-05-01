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
	///////////�̹��� �ε��ϱ�/////////
	readBmpRect("asset/item.bmp", 146, 66, 144, 64, &sprite);

	///////////�浹ü �߰��ϱ�////////
	addCollider(new AABB(40, 32, 16, 16, 0));

	///////////������ ���ӽð� �ʱ�ȭ//////
	lifeTime = 5;
}

void HPItem::update()
{
	lifeTime = lifeTime - getDelteTime();

	if (lifeTime < 0)  //������ ���� �ð��� ��� ����
	{
		parentObj->delChildObj(this);
	}
}

void HPItem::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	if (obj->getTag() == 0 && strcmp(obj->getName(), "������") == 0)
	{
		parentObj->delChildObj(this);
	}
}