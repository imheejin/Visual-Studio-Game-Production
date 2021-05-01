#include "stdafx.h"
#include "PlayerDeath.h"
#include "GameObjectPool.h"
#include "Player.h"
#include "GameManager.h"

PlayerDeath::PlayerDeath(float px, float py) : Animation("나루토죽음", 0, true, px, py)
{
	
}

PlayerDeath::~PlayerDeath()
{
}

void PlayerDeath::init()
{
	//////////애니메이션 로드/////////
	for (int i = 0; i < 8; i++)
	{
		Sprite sprite;

		readBmpRect("asset/나루토.bmp", i*(72 + 2), 1451, 72, 72, &sprite);
		addFrame(sprite, 0);
	}
}

void PlayerDeath::OnFrameChange(int id, int frame)
{
	if (frame == 0)
	{
		GameObjectPool * pool = GameObjectPool::instance();
		
		//[1]죽음 애니메이션 제거
		pool->delGameObject(this);

		//[2]게임 매니저를 통해서..플레이어 리스폰 하기
		GameManager::instance()->playerSpawn();
	
	}
}