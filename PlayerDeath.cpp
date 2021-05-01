#include "stdafx.h"
#include "PlayerDeath.h"
#include "GameObjectPool.h"
#include "Player.h"
#include "GameManager.h"

PlayerDeath::PlayerDeath(float px, float py) : Animation("����������", 0, true, px, py)
{
	
}

PlayerDeath::~PlayerDeath()
{
}

void PlayerDeath::init()
{
	//////////�ִϸ��̼� �ε�/////////
	for (int i = 0; i < 8; i++)
	{
		Sprite sprite;

		readBmpRect("asset/������.bmp", i*(72 + 2), 1451, 72, 72, &sprite);
		addFrame(sprite, 0);
	}
}

void PlayerDeath::OnFrameChange(int id, int frame)
{
	if (frame == 0)
	{
		GameObjectPool * pool = GameObjectPool::instance();
		
		//[1]���� �ִϸ��̼� ����
		pool->delGameObject(this);

		//[2]���� �Ŵ����� ���ؼ�..�÷��̾� ������ �ϱ�
		GameManager::instance()->playerSpawn();
	
	}
}