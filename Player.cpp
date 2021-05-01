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

Player::Player(float px, float py) : Animation("������", 0, true, px, py)
{
}

Player::~Player()
{
}

void Player::init()
{

	////////////�ִϸ��̼� �̹��� �ε�/////////////
	//�̵� �ִϸ��̼� - 0 ��
	for (int i = 0; i < 6; i++)
	{
		Sprite sprite;

		readBmpRect("asset/������.bmp", i*(96+2), 492, 96, 72, &sprite);

		////////��������Ʈ�� �浹ü �߰��ϱ�////////		
		sprite.addCollider(new AABB(30, 35, 60, 30, 0) , px, py);

		addFrame(sprite, run);  //0 - �� �ִϸ��̼�
	}

	//���� �ִϸ��̼� - 1��
	//////////�浹ü ��ġ/ũ�� �迭 �����//////////
	int colx[11] = { 40,  50, 50, 40, 35,    30, 35, 35, 40, 40,    40 };
	int coly[11] = { 35, -5 ,-15,-5 ,-10,   -15,-15, 10, 35, 30,    25 };
	int colw[11] = { 40,  30, 25, 45, 45,    40, 40, 40, 40, 40,    35 };
	int colh[11] = { 30,  55, 55, 35, 35,    35, 65, 50, 30, 35,    40 };

	for (int i = 0; i < 11; i++)
	{
		Sprite sprite;

		readBmpRect("asset/������.bmp", i*(80 + 2), 1599, 80, 112, &sprite);

		/////////////��������Ʈ �浹ü �߰��ϱ�////////
		sprite.addCollider(new AABB(colx[i], coly[i], colw[i], colh[i], 0), px, py);

		////////sprite�� ��Ŀ ����Ʈ�� �����ؼ�..�ִϸ��̼� �̹���..��ġ�� ����//////
		sprite.ay =  40;  //�����̵� +, �Ʒ����̵� -
		sprite.ax = -15;  //�����̵� +, �������̵� -

		addFrame(sprite, jump);  //1- �� �ִϸ��̼�
	}

	//���� �ִϸ��̼� - 2��
	for (int i = 0; i < 6; i++)
	{
		Sprite sprite;

		readBmpRect("asset/������.bmp", i*(160 + 2), 3231, 160, 120, &sprite);

		/////////////��������Ʈ�� �浹ü �߰��ϱ�//////////////
		sprite.addCollider(new AABB(40, 20, 40, 50, 0), px, py);

		////////sprite�� ��Ŀ ����Ʈ�� �����ؼ�..�ִϸ��̼� �̹���..��ġ�� ����//////
		sprite.ay = 45;  //�����̵� +, �Ʒ����̵� -
		sprite.ax = 0;   //�����̵� +, �������̵� -

		addFrame(sprite, attack);  //2- �� �ִϸ��̼�
	}
	
	//Hit �ִϸ��̼� - 3��
	for (int i = 0; i < 2; i++)
	{
		Sprite sprite;

		readBmpRect("asset/������.bmp", i*(64 + 2), 1713, 64, 64, &sprite);
		addFrame(sprite, hit);
	}

	//////////�ִϸ��̼� �ӵ� �����ϱ�////////////
	setFrameDelay(0.1);

	///////////�̵� �ӵ� �����ϱ�/////////////////
	runSpeed  = 100;
	jumpSpeed = 50;

	////////////�ִϸ��̼� ���� �ʱ�ȭ////////////
	state = run;
}

void Player::update()
{
	////////////�ִϸ��̼� State Machine////////////
	if (state == run)
	{
		////////ȭ��ũ�� ���ϱ�////////
		int width = getClientWidth();

		////////�̵��Ÿ� ���//////////
		float dist = runSpeed * getDelteTime();

		////////�¿� �̵�Ű///////////
		if (getKey(VK_RIGHT) == true &&  px < width - 96)
		{
			//[1]�÷��̾� �̵�
			translate(dist, 0);

			//[2]��潺ũ�� ��Ű��
			GameObjectPool * pool = GameObjectPool::instance();
			GameObject *BG2       = pool->find("���2");

			if (BG2 != NULL)
			{
				BG2->translate(-dist*0.5, 0);
			}
		}

		if (getKey(VK_LEFT) == true &&  px > -30)
		{
			translate(-dist, 0);
		}

		///////���� Ű//////////////
		if (getKeyDown(VK_UP) == true) //���� ���·� ����
		{
			play(jump);   //�ִϸ��̼� ����
			state = jump; //���� ���·� ����
		}

		/////���� Ű/////////////////
		if (getKeyDown(VK_SPACE) == true) //���� ���·� ����
		{
			play(attack);  //�ִϸ��̼� ����
			state = attack;//���� ���·� ����
		}

		/////////�÷��̾ ������ ��ġ ��Ű��///////////
		translate(0, 5);
	}
	else if (state == jump) {

		float dist = jumpSpeed * getDelteTime();

		//[1]�ڵ����� �̵�	
		//translate(dist, 0);

		//[2]�̵�Ű�� �̵�
		if (getKey(VK_RIGHT) == true)
		{
			translate(dist, 0);

			//[2]��潺ũ�� ��Ű��
			GameObjectPool * pool = GameObjectPool::instance();
			GameObject *BG2 = pool->find("���2");

			if (BG2 != NULL)
			{
				BG2->translate(-dist * 0.5, 0);
			}
		}
		
		if (getKey(VK_LEFT) == true)
		{
			translate(-dist, 0);
		}

		////////���� �ִϸ��̼� �Ϸ�////////
		if (getFrameNum() == 10)  //run ���·� ����
		{
			play(run);   //run �ִϸ��̼�
			state = run; //run ���·�...����

			

		}

	}
	else if (state == attack) {

		//////���� �ִϸ��̼� �Ϸ�////////
		if (getFrameNum() == 5)  //run ���·� ����
		{
			///////�󼾰� �߻�//////
			GameObjectPool * pool = GameObjectPool::instance();

			pool->addGameObject(new Rasengan(px+50, py+10), 2);

			play(run);
			state = run;		
		}

		/////////�÷��̾ ������ ��ġ ��Ű��///////////
		translate(0, 5);

	}
	else if (state == hit) {

		////////���� �ִϸ��̼��� �����ϱ�///////
		if (getFrameNum() == 1)  //run �ִϸ��̼����� ����
		{
			play(run);
			state = run;

			translate(-50, 0);  //��ǥ�� �ڷ�..�̵���Ű��

			setFrameDelay(0.1);  //���� �ִϸ��̼� �ӵ���..������
		}

	}

	
}

void Player::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	GameManager     * manager = GameManager::instance();
	GameObjectPool  * pool	  = GameObjectPool::instance();

	/////////////����(����)���� �浹////////////////////
	if (strcmp(obj->getName(), "����") == 0 && otherCol->getId() == 0)
	{
		if (state != jump) //�����̸�...�÷��̾�� ���ظ� ��������
		{
			//��Ʈ �ִϸ��̼�����..��ȯ
			play(hit);
			state = hit;
			setFrameDelay(1);    //�ִϸ��̼� �ӵ��� ��������		

			//�������� �浹..���ع���
			manager->addHP(-10); 

			//////////Flying ���̺� �����///////
			pool->addGameObject(new FlyingLabel(L"ü��: -10", 0x00ff0000, px, py), 3);
		}
	}

	////////////////������ ����(��, Į) �浹 �˻��ϱ�//////////////////
	if (strcmp(obj->getName(), "����") == 0 && (otherCol->getId() == 1 || otherCol->getId() == 2))
	{
		//��Ʈ �ִϸ��̼�����..��ȯ
		play(hit);
		state = hit;
		setFrameDelay(1);    //�ִϸ��̼� �ӵ��� ��������		

		//�������� �浹..���ع���
		manager->addHP(-10);

		//////////Flying ���̺� �����///////
		pool->addGameObject(new FlyingLabel(L"ü��: -10", 0x00ff0000, px, py), 3);
	}
}
/////////////////OnCollisionEnter���� ���� �ص� ��//////////////
void Player::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
	GameObjectPool * pool    = GameObjectPool::instance();
	GameManager    * manager = GameManager::instance();

	//[1]�÷��̾�� ���� �浹�˻�
	if (obj->getTag() == 1 && strcmp(obj->getName(), "��") == 0)
	{
		//��Ʈ �ִϸ��̼�����..��ȯ
		play(hit);
		state = hit;

		setFrameDelay(1);     //�ִϸ��̼� �ӵ��� ��������		
		manager->addHP(-10);  //hp = hp - 10;      //�� �浹 ����

		//////////Flying ���̺� �����///////
		pool->addGameObject(new FlyingLabel(L"ü��: -10", 0x00ff0000, px, py), 3);
	}

	//[2]�÷��̾�� ������ �浹�˻�
	if (obj->getTag() == 1 && strcmp(obj->getName(), "����") == 0 && otherCol->getId() == 0)
	{
		//��Ʈ �ִϸ��̼�����..��ȯ
		play(hit);
		state = hit;

		setFrameDelay(1);    //�ִϸ��̼� �ӵ��� ��������		
		manager->addHP(-20); //hp = hp - 20;      //���� �浹 ����

		//////////Flying ���̺� �����///////
		pool->addGameObject(new FlyingLabel(L"ü��: -20", 0x00ff0000, px, py), 3);
	}

	//[3]�÷��̾�� ��(���ڳ�)�� �浹�˻�
	if (obj->getTag() == 1 && strcmp(obj->getName(), "ū��") == 0)
	{
		//��Ʈ �ִϸ��̼�����..��ȯ
		play(hit);
		state = hit;

		setFrameDelay(1);    //�ִϸ��̼� �ӵ��� ��������		
		manager->addHP(-30); //hp = hp - 30;      //ū�� �浹 ����

		//////////Flying ���̺� �����///////
		pool->addGameObject(new FlyingLabel(L"ü��: -30", 0x00ff0000, px, py), 3);
	}

	//[4]ü�� ������ ȹ�� �˻�
	if (obj->getTag() == 5 && strcmp(obj->getName(), "HPItem") == 0)
	{
		//hp = hp + 50;
		manager->addHP(50);

		//////////Flying ���̺� �����///////
		pool->addGameObject(new FlyingLabel(L"ü��: +50", 0x000000ff, px, py), 3);	
	}

	if (manager->getHP() < 0 && getAlive() == true)
	{
		///////////�÷��̾� ����///////////
		GameObjectPool * pool = GameObjectPool::instance();
		pool->delGameObject(this);

		//////////�÷��̾� ���� �ִϸ��̼�////////
		pool->addGameObject(new PlayerDeath(px, py), 2);
	}
}

void Player::AniTest()
{
	/////////////////////////////////////////////////
	//�ִϸ��̼� �׽�Ʈ �ϱ�
	if (getKeyDown('1') == true)
	{
		play(0);  //0�� �ִϸ��̼� �÷���
	}

	if (getKeyDown('2') == true)
	{
		play(1);  //1�� �ִϸ��̼� �÷���
	}

	if (getKeyDown('3') == true)
	{
		play(2);  //2�� �ִϸ��̼� �÷���
	}
}