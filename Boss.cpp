#include "stdafx.h"
#include "Boss.h"
#include "input.h"
#include "EndingScene.h"
#include "FrameWork.h"
#include "GameObjectPool.h"
#include "timer.h"
#include "BossFx.h"

Boss::Boss(float px, float py) : Animation("보스", 1, true, px, py)
{
}

Boss::~Boss()
{
}

void Boss::init()
{
	//좌우 플립지정//
	hFlip = true;

	////////걷기-이동 애니메이션/////
	for (int i = 0; i < 6; i++)
	{
		Sprite sprite;

		readBmpRect("asset/boss.bmp", i*(32 + 2), 377, 32, 72, &sprite);

		////////충돌체 추가하기///////
		sprite.addCollider(new AABB(0, 0, 32, 72, 0), px, py);

		addFrame(sprite, walk);
	}

	///////공격1 애니메이션/////////
	int colx1[8] = {20 , 0, -35, -50,   -50,-50, 0 , 15};
	int coly1[8] = {18 , 18, 13,  18,    18, 18, 40, 40};
	int colw1[8] = {30 , 30, 30,  45,    45, 45, 30, 30};
	int colh1[8] = {26 , 26, 30,  30,    30, 30, 20, 20};

	for (int i = 0; i < 8; i++)
	{
		Sprite sprite;

		readBmpRect("asset/boss.bmp", i*(109 + 2), 148 , 109, 64, &sprite);

		////////////앵커 포인터 조정하기//////////
		sprite.ax = 50;

		////////충돌체 추가하기///////
		sprite.addCollider(new AABB(-5, 0, 35, 64, 0), px, py);  //보스 몸통
		
		sprite.addCollider(new AABB(colx1[i], coly1[i], colw1[i], colh1[i], 1), px, py);  //보스의 뱀 공격 충돌체

		addFrame(sprite, attack1);
	}

	///////공격2 애니메이션/////////
	int colx2[5] = {-100, -65 , -65, -95, -95};
	int coly2[5] = {  15,  0  ,  30,  30,  30};
	int colw2[5] = {  50,  40 ,  45,  65,  65};
	int colh2[5] = {  65,  45 ,  45,  35,  6};

	for (int i = 0; i < 5; i++)	
	{
		Sprite sprite;

		readBmpRect("asset/boss.bmp", i*(183 + 2), 2785, 183, 162, &sprite);
		
		////////////앵커 포인터 조정하기//////////
		sprite.ax = 150;
		sprite.ay = 80;

		////////충돌체 추가하기///////
		sprite.addCollider(new AABB(5, 0, 30, 64, 0), px, py);   //보스 몸통 충돌체

		sprite.addCollider(new AABB(colx2[i], coly2[i], colw2[i], colh2[i], 2), px, py);  //보스의 칼 공격 충돌체

		addFrame(sprite, attack2);
	}

	////////죽음 애니메이션///////////
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBmpRect("asset/boss.bmp", i*(72 + 2), 1189, 72, 53, &sprite);

		////////////앵커 포인터 조정하기//////////
		sprite.ay = -35;

		addFrame(sprite, death);
	}

	////////////hp, 이동속도, 공격거리, 시간 초기화하기////////////
	hp		   = 200;
	speed	   = 50;
	
	attackDist   = 120;
	attack1Delay = 3;

	////////////보스 상태 초기화/////////
	state = walk;

	////////////애니메이션 플레이-테스트//////
	//play(attack2);

}

void Boss::update()
{
#if 1
	///////플레이어 거리구하기////////
	GameObject * player = GameObjectPool::instance()->find("나루토");

	if (player != NULL)  //플레이어를 찾음
	{
		float dist = px - player->getX();

		if (state == walk)  //플레이어를 향해서..접근
		{
			if (dist > attackDist)  //플레이어가 공격거리 밖에 있음 - 접근
			{
				float d = speed * getDelteTime();
				translate(-d, 0);
			}
			else {  //공격 시작

				attack1Delay = 3.0f;  //첫번째 공격시간 리셋

				state = attack1;
				play(attack1);

			}
		}
		else if (state == attack1){  //첫번째 공격 

			attack1Delay = attack1Delay - getDelteTime();

			if (attack1Delay < 0)  //두번째 공격으로 전환
			{
				state = attack2;
				play(attack2);
			}

			if (dist > attackDist + 50)  //거리가 멀어지면....다시..플레이어를 향해 접근
			{
				state = walk;
				play(walk);
			}

		}
		else if (state == attack2) {  //두번째 공격

			if (dist > attackDist + 50)  //거리가 멀어지만...다시..플레이어를 향해 접근
			{
				state = walk;
				play(walk);
			}

		}
	}
#endif
}

void Boss::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)
{	
	if (strcmp(obj->getName(), "라센간") == 0 && myCol->getId() == 0)
	{
		hp = hp - 100;

		//////////보스 hp가 모두 소진됨//////
		if (hp < 0)
		{
			play(death);
		}		
	}

	//////////////////보스가 나루토와 충돌했을때////////////////////
	if (strcmp(obj->getName(), "나루토") == 0 && myCol->getId() == 0)
	{
		/////////보스 사라지는 효과///////////
		GameObjectPool::instance()->addGameObject(new BossFx(px, py-10), 2);

		////////보스를 뒤로 이동시킴//////////
		translate(attackDist * 1.5, 0);
	}
}

void Boss::OnFrameChange(int id, int frameNum)
{
	if (id == death && frameNum == 0)
	{
		//[참고] 게임데이타 과련 처리를 위해서는 게임매니저를 통한 씬 전환이 바람직함
		FrameWork::instance()->LoadScene(new EndingScene());		
	}
}

void Boss::aniTest()
{
	if (getKeyDown('1') == true)
	{
		play(walk);
	}

	if (getKeyDown('2') == true)
	{
		play(attack1);
	}

	if (getKeyDown('3') == true)
	{
		play(attack2);
	}

	if (getKeyDown('4') == true)
	{
		play(death);
	}
}