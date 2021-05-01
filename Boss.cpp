#include "stdafx.h"
#include "Boss.h"
#include "input.h"
#include "EndingScene.h"
#include "FrameWork.h"
#include "GameObjectPool.h"
#include "timer.h"
#include "BossFx.h"

Boss::Boss(float px, float py) : Animation("����", 1, true, px, py)
{
}

Boss::~Boss()
{
}

void Boss::init()
{
	//�¿� �ø�����//
	hFlip = true;

	////////�ȱ�-�̵� �ִϸ��̼�/////
	for (int i = 0; i < 6; i++)
	{
		Sprite sprite;

		readBmpRect("asset/boss.bmp", i*(32 + 2), 377, 32, 72, &sprite);

		////////�浹ü �߰��ϱ�///////
		sprite.addCollider(new AABB(0, 0, 32, 72, 0), px, py);

		addFrame(sprite, walk);
	}

	///////����1 �ִϸ��̼�/////////
	int colx1[8] = {20 , 0, -35, -50,   -50,-50, 0 , 15};
	int coly1[8] = {18 , 18, 13,  18,    18, 18, 40, 40};
	int colw1[8] = {30 , 30, 30,  45,    45, 45, 30, 30};
	int colh1[8] = {26 , 26, 30,  30,    30, 30, 20, 20};

	for (int i = 0; i < 8; i++)
	{
		Sprite sprite;

		readBmpRect("asset/boss.bmp", i*(109 + 2), 148 , 109, 64, &sprite);

		////////////��Ŀ ������ �����ϱ�//////////
		sprite.ax = 50;

		////////�浹ü �߰��ϱ�///////
		sprite.addCollider(new AABB(-5, 0, 35, 64, 0), px, py);  //���� ����
		
		sprite.addCollider(new AABB(colx1[i], coly1[i], colw1[i], colh1[i], 1), px, py);  //������ �� ���� �浹ü

		addFrame(sprite, attack1);
	}

	///////����2 �ִϸ��̼�/////////
	int colx2[5] = {-100, -65 , -65, -95, -95};
	int coly2[5] = {  15,  0  ,  30,  30,  30};
	int colw2[5] = {  50,  40 ,  45,  65,  65};
	int colh2[5] = {  65,  45 ,  45,  35,  6};

	for (int i = 0; i < 5; i++)	
	{
		Sprite sprite;

		readBmpRect("asset/boss.bmp", i*(183 + 2), 2785, 183, 162, &sprite);
		
		////////////��Ŀ ������ �����ϱ�//////////
		sprite.ax = 150;
		sprite.ay = 80;

		////////�浹ü �߰��ϱ�///////
		sprite.addCollider(new AABB(5, 0, 30, 64, 0), px, py);   //���� ���� �浹ü

		sprite.addCollider(new AABB(colx2[i], coly2[i], colw2[i], colh2[i], 2), px, py);  //������ Į ���� �浹ü

		addFrame(sprite, attack2);
	}

	////////���� �ִϸ��̼�///////////
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBmpRect("asset/boss.bmp", i*(72 + 2), 1189, 72, 53, &sprite);

		////////////��Ŀ ������ �����ϱ�//////////
		sprite.ay = -35;

		addFrame(sprite, death);
	}

	////////////hp, �̵��ӵ�, ���ݰŸ�, �ð� �ʱ�ȭ�ϱ�////////////
	hp		   = 200;
	speed	   = 50;
	
	attackDist   = 120;
	attack1Delay = 3;

	////////////���� ���� �ʱ�ȭ/////////
	state = walk;

	////////////�ִϸ��̼� �÷���-�׽�Ʈ//////
	//play(attack2);

}

void Boss::update()
{
#if 1
	///////�÷��̾� �Ÿ����ϱ�////////
	GameObject * player = GameObjectPool::instance()->find("������");

	if (player != NULL)  //�÷��̾ ã��
	{
		float dist = px - player->getX();

		if (state == walk)  //�÷��̾ ���ؼ�..����
		{
			if (dist > attackDist)  //�÷��̾ ���ݰŸ� �ۿ� ���� - ����
			{
				float d = speed * getDelteTime();
				translate(-d, 0);
			}
			else {  //���� ����

				attack1Delay = 3.0f;  //ù��° ���ݽð� ����

				state = attack1;
				play(attack1);

			}
		}
		else if (state == attack1){  //ù��° ���� 

			attack1Delay = attack1Delay - getDelteTime();

			if (attack1Delay < 0)  //�ι�° �������� ��ȯ
			{
				state = attack2;
				play(attack2);
			}

			if (dist > attackDist + 50)  //�Ÿ��� �־�����....�ٽ�..�÷��̾ ���� ����
			{
				state = walk;
				play(walk);
			}

		}
		else if (state == attack2) {  //�ι�° ����

			if (dist > attackDist + 50)  //�Ÿ��� �־�����...�ٽ�..�÷��̾ ���� ����
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
	if (strcmp(obj->getName(), "�󼾰�") == 0 && myCol->getId() == 0)
	{
		hp = hp - 100;

		//////////���� hp�� ��� ������//////
		if (hp < 0)
		{
			play(death);
		}		
	}

	//////////////////������ ������� �浹������////////////////////
	if (strcmp(obj->getName(), "������") == 0 && myCol->getId() == 0)
	{
		/////////���� ������� ȿ��///////////
		GameObjectPool::instance()->addGameObject(new BossFx(px, py-10), 2);

		////////������ �ڷ� �̵���Ŵ//////////
		translate(attackDist * 1.5, 0);
	}
}

void Boss::OnFrameChange(int id, int frameNum)
{
	if (id == death && frameNum == 0)
	{
		//[����] ���ӵ���Ÿ ���� ó���� ���ؼ��� ���ӸŴ����� ���� �� ��ȯ�� �ٶ�����
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