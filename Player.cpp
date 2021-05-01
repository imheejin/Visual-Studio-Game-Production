#include "stdafx.h"
#include "Player.h"
#include "timer.h"
#include "input.h"
#include "graphic.h"
#include "Rasengan.h"
#include "GameObjectPool.h"
#include "PlayerDeath.h"
#include "FlyingLabel.h"
#include "GameManager.h"

Player::Player(float px, float py) : Animation("나루토", 0, true, px, py)
{
}

Player::~Player()
{
}

void Player::init()
{

	////////////애니메이션 이미지 로드/////////////
	//이동 애니메이션 - 0 번
	for (int i = 0; i < 6; i++)
	{
		Sprite sprite;

		readBmpRect("asset/나루토.bmp", i*(96+2), 492, 96, 72, &sprite);

		////////스프라이트에 충돌체 추가하기////////		
		sprite.addCollider(new AABB(30, 35, 60, 30, 0) , px, py);

		addFrame(sprite, run);  //0 - 번 애니메이션
	}

	//점프 애니메이션 - 1번
	//////////충돌체 위치/크기 배열 만들기//////////
	int colx[11] = { 40,  50, 50, 40, 35,    30, 35, 35, 40, 40,    40 };
	int coly[11] = { 35, -5 ,-15,-5 ,-10,   -15,-15, 10, 35, 30,    25 };
	int colw[11] = { 40,  30, 25, 45, 45,    40, 40, 40, 40, 40,    35 };
	int colh[11] = { 30,  55, 55, 35, 35,    35, 65, 50, 30, 35,    40 };

	for (int i = 0; i < 11; i++)
	{
		Sprite sprite;

		readBmpRect("asset/나루토.bmp", i*(80 + 2), 1599, 80, 112, &sprite);

		/////////////스프라이트 충돌체 추가하기////////
		sprite.addCollider(new AABB(colx[i], coly[i], colw[i], colh[i], 0), px, py);

		////////sprite의 앵커 포인트를 조정해서..애니메이션 이미지..위치를 맞춤//////
		sprite.ay =  40;  //위로이동 +, 아래로이동 -
		sprite.ax = -15;  //왼쪽이동 +, 오른쪽이동 -

		addFrame(sprite, jump);  //1- 번 애니메이션
	}

	//공격 애니메이션 - 2번
	for (int i = 0; i < 6; i++)
	{
		Sprite sprite;

		readBmpRect("asset/나루토.bmp", i*(160 + 2), 3231, 160, 120, &sprite);

		/////////////스프라이트에 충돌체 추가하기//////////////
		sprite.addCollider(new AABB(40, 20, 40, 50, 0), px, py);

		////////sprite의 앵커 포인트를 조정해서..애니메이션 이미지..위치를 맞춤//////
		sprite.ay = 45;  //위로이동 +, 아래로이동 -
		sprite.ax = 0;   //왼쪽이동 +, 오른쪽이동 -

		addFrame(sprite, attack);  //2- 번 애니메이션
	}
	
	//Hit 애니메이션 - 3번
	for (int i = 0; i < 2; i++)
	{
		Sprite sprite;

		readBmpRect("asset/나루토.bmp", i*(64 + 2), 1713, 64, 64, &sprite);
		addFrame(sprite, hit);
	}

	//////////애니메이션 속도 지정하기////////////
	setFrameDelay(0.1);

	///////////이동 속도 지정하기/////////////////
	runSpeed  = 100;
	jumpSpeed = 50;

	////////////애니메이션 상태 초기화////////////
	state = run;
}

void Player::update()
{
	////////////애니메이션 State Machine////////////
	if (state == run)
	{
		////////화면크기 구하기////////
		int width = getClientWidth();

		////////이동거리 계산//////////
		float dist = runSpeed * getDelteTime();

		////////좌우 이동키///////////
		if (getKey(VK_RIGHT) == true &&  px < width - 96)
		{
			//[1]플레이어 이동
			translate(dist, 0);

			//[2]배경스크롤 시키기
			GameObjectPool * pool = GameObjectPool::instance();
			GameObject *BG2       = pool->find("배경2");

			if (BG2 != NULL)
			{
				BG2->translate(-dist*0.5, 0);
			}
		}

		if (getKey(VK_LEFT) == true &&  px > -30)
		{
			translate(-dist, 0);
		}

		///////점프 키//////////////
		if (getKeyDown(VK_UP) == true) //점프 상태로 변경
		{
			play(jump);   //애니메이션 변경
			state = jump; //점프 상태로 변경
		}

		/////공격 키/////////////////
		if (getKeyDown(VK_SPACE) == true) //공격 상태로 변경
		{
			play(attack);  //애니메이션 변경
			state = attack;//공격 상태로 변경
		}

		/////////플레이어를 지형에 위치 시키기///////////
		translate(0, 5);
	}
	else if (state == jump) {

		float dist = jumpSpeed * getDelteTime();

		//[1]자동으로 이동	
		//translate(dist, 0);

		//[2]이동키로 이동
		if (getKey(VK_RIGHT) == true)
		{
			translate(dist, 0);

			//[2]배경스크롤 시키기
			GameObjectPool * pool = GameObjectPool::instance();
			GameObject *BG2 = pool->find("배경2");

			if (BG2 != NULL)
			{
				BG2->translate(-dist * 0.5, 0);
			}
		}
		
		if (getKey(VK_LEFT) == true)
		{
			translate(-dist, 0);
		}

		////////점프 애니메이션 완료////////
		if (getFrameNum() == 10)  //run 상태로 변경
		{
			play(run);   //run 애니메이션
			state = run; //run 상태로...변경

			

		}

	}
	else if (state == attack) {

		//////공격 애니메이션 완료////////
		if (getFrameNum() == 5)  //run 상태로 변경
		{
			///////라센간 발사//////
			GameObjectPool * pool = GameObjectPool::instance();

			pool->addGameObject(new Rasengan(px+50, py+10), 2);

			play(run);
			state = run;		
		}

		/////////플레이어를 지형에 위치 시키기///////////
		translate(0, 5);

	}
	else if (state == hit) {

		////////원래 애니메이션을 복구하기///////
		if (getFrameNum() == 1)  //run 애니메이션으로 가기
		{
			play(run);
			state = run;

			translate(-50, 0);  //좌표를 뒤로..이동시키기

			setFrameDelay(0.1);  //원래 애니메이션 속도로..복구함
		}

	}

	
}

void Player::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	GameManager     * manager = GameManager::instance();
	GameObjectPool  * pool	  = GameObjectPool::instance();

	/////////////보스(몸통)와의 충돌////////////////////
	if (strcmp(obj->getName(), "보스") == 0 && otherCol->getId() == 0)
	{
		if (state != jump) //점프이면...플레이어는 피해를 받지않음
		{
			//히트 애니메이션으로..전환
			play(hit);
			state = hit;
			setFrameDelay(1);    //애니메이션 속도를 느리게함		

			//보스와의 충돌..피해받음
			manager->addHP(-10); 

			//////////Flying 레이블 만들기///////
			pool->addGameObject(new FlyingLabel(L"체력: -10", 0x00ff0000, px, py), 3);
		}
	}

	////////////////보스의 공격(뱀, 칼) 충돌 검사하기//////////////////
	if (strcmp(obj->getName(), "보스") == 0 && (otherCol->getId() == 1 || otherCol->getId() == 2))
	{
		//히트 애니메이션으로..전환
		play(hit);
		state = hit;
		setFrameDelay(1);    //애니메이션 속도를 느리게함		

		//보스와의 충돌..피해받음
		manager->addHP(-10);

		//////////Flying 레이블 만들기///////
		pool->addGameObject(new FlyingLabel(L"체력: -10", 0x00ff0000, px, py), 3);
	}
}
/////////////////OnCollisionEnter에서 구현 해도 됨//////////////
void Player::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	GameObjectPool * pool    = GameObjectPool::instance();
	GameManager    * manager = GameManager::instance();

	//[1]플레이어와 뱀의 충돌검사
	if (obj->getTag() == 1 && strcmp(obj->getName(), "뱀") == 0)
	{
		//히트 애니메이션으로..전환
		play(hit);
		state = hit;

		setFrameDelay(1);     //애니메이션 속도를 느리게함		
		manager->addHP(-10);  //hp = hp - 10;      //뱀 충돌 피해

		//////////Flying 레이블 만들기///////
		pool->addGameObject(new FlyingLabel(L"체력: -10", 0x00ff0000, px, py), 3);
	}

	//[2]플레이어와 닌자의 충돌검사
	if (obj->getTag() == 1 && strcmp(obj->getName(), "닌자") == 0 && otherCol->getId() == 0)
	{
		//히트 애니메이션으로..전환
		play(hit);
		state = hit;

		setFrameDelay(1);    //애니메이션 속도를 느리게함		
		manager->addHP(-20); //hp = hp - 20;      //닌자 충돌 피해

		//////////Flying 레이블 만들기///////
		pool->addGameObject(new FlyingLabel(L"체력: -20", 0x00ff0000, px, py), 3);
	}

	//[3]플레이어와 낫(닌자낫)의 충돌검사
	if (obj->getTag() == 1 && strcmp(obj->getName(), "큰낫") == 0)
	{
		//히트 애니메이션으로..전환
		play(hit);
		state = hit;

		setFrameDelay(1);    //애니메이션 속도를 느리게함		
		manager->addHP(-30); //hp = hp - 30;      //큰낫 충돌 피해

		//////////Flying 레이블 만들기///////
		pool->addGameObject(new FlyingLabel(L"체력: -30", 0x00ff0000, px, py), 3);
	}

	//[4]체력 아이템 획득 검사
	if (obj->getTag() == 5 && strcmp(obj->getName(), "HPItem") == 0)
	{
		//hp = hp + 50;
		manager->addHP(50);

		//////////Flying 레이블 만들기///////
		pool->addGameObject(new FlyingLabel(L"체력: +50", 0x000000ff, px, py), 3);	
	}

	if (manager->getHP() < 0 && getAlive() == true)
	{
		///////////플레이어 제거///////////
		GameObjectPool * pool = GameObjectPool::instance();
		pool->delGameObject(this);

		//////////플레이어 제거 애니메이션////////
		pool->addGameObject(new PlayerDeath(px, py), 2);
	}
}

void Player::AniTest()
{
	/////////////////////////////////////////////////
	//애니메이션 테스트 하기
	if (getKeyDown('1') == true)
	{
		play(0);  //0번 애니메이션 플레이
	}

	if (getKeyDown('2') == true)
	{
		play(1);  //1번 애니메이션 플레이
	}

	if (getKeyDown('3') == true)
	{
		play(2);  //2번 애니메이션 플레이
	}
}