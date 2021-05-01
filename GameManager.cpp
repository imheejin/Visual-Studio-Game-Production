#include "stdafx.h"
#include "GameManager.h"
#include "GameObjectPool.h"
#include "Label.h"
#include "Icon.h"
#include "Player.h"
#include "Gameover.h"
#include "Boss.h"

GameManager * GameManager::manager=NULL;

GameManager::GameManager() : GameObject("���ӸŴ���", 6, true, 0,0)
{}

GameManager::~GameManager()
{
	/////////���� �Ŵ���..��ü ���� �����͸� NULL�� ������///////
	manager = NULL;
}

GameManager * GameManager::instance()
{
	if (manager == NULL)
	{
		manager = new GameManager();
	}

	return manager;
}

void GameManager::init()
{
	GameObjectPool * pool = GameObjectPool::instance();
	
	////////ü��/���� ���� ����ϱ�////////
	const char * ttf = "asset/ttf/godoMaum.ttf";
	
	pool->addGameObject(new Label(L"ü��:", ttf , 32, 0x00ffffff, 10, 32), 3);
	pool->addGameObject(new Label(L"����:", ttf,  32, 0x00ffffff, 10, 65), 3);

	/////////���Ӽ� �ʱ�ȭ �ϱ�//////////////
	games = 3;

	/////////���� ���Ӽ� ������ �����///////
	for (int i = 0; i < MAX_GAMES; i++)
	{
		icons[i] = new Icon(420 + i * 44, 5);

		if (i < games)
		{
			icons[i]->setSate(true);
		}
		else {
			icons[i]->setSate(false);
		}

		pool->addGameObject(icons[i], 3);
	}
	
	/////////////���� ���� �ʱ�ȭ//////////////
	score		= 0;
	scoreLabel = new Label(L"0", ttf, 40, 0x000000ff, 66, 65);
	pool->addGameObject(scoreLabel, 3);

	/////////////ü�� ���� �ʱ�ȭ//////////////
	hp			= 100;

	hpBar = new Bar(70, 10, 150, 20);
	pool->addGameObject(hpBar, 3);

	hpLabel = new Label(L"100", ttf, 32, 0x000000ff, 120, 30);
	pool->addGameObject(hpLabel, 3);

	hpBar->setPosition(1.0f);

	//////////////���� ���� ����..�ʱ�ȭ////////
	bossSpawned=false;

	////////////���� ���� ����ϱ�/////////////
	pool->addGameObject(new Label(L"2D ���� ���� ������Ʈ V1.0", ttf, 18, 0x00ffffff, 450, 150), 3);
	pool->addGameObject(new Label(L"������: ȫ�浿", ttf, 18, 0x00ffffff, 450, 165), 3);
	pool->addGameObject(new Label(L"���߱Ⱓ: 2019��4��~5��", ttf, 18, 0x00ffffff, 450, 180), 3);

	///////////�������� �׽�Ʈ �ϱ�////////////
	//pool->addGameObject(new Gameover(230, 10), 3);
}

void GameManager::addScore(int point)
{
	score = score + point;
	printScore();
}

void GameManager::addHP(int point)
{
	hp = hp + point;
	
	///////hp �ִ�ġ///////
	if (hp > 100)
	{
		hp = 100;
	}

	//////hp ȭ�� ���/////
	printHP();
}

int GameManager::getHP()
{
	return hp;
}

void GameManager::printHP()
{
	//////HP�� ���ڷ� ���//////
	WCHAR temp[32]=L"0";

	if (hp > 0)
	{
		wsprintf(temp, L"%d", hp);
	}

	hpLabel->setText(temp);

	///////HP ���α׷��ú��(Progressive Bar)�� ���//////
	float p = (float)hp / 100.0f;
	hpBar->setPosition(p);
}

void GameManager::printScore()
{
	WCHAR temp[32];	
	wsprintf(temp, L"%d", score);

	scoreLabel->setText(temp);
}

void GameManager::playerSpawn()
{
	//[1]���Ӽ� ����
	games--;

	if (games >= 0)
	{
		icons[games]->setSate(false);  //���Ӽ� ǥ�� ������ ����

		//[2]�÷��̾� ������ - ��� ��ġ ����
		
		if (bossSpawned == false)  //������������ ��� �������� ����
		{
			//����� ó������ ������
			GameObject * bg = GameObjectPool::instance()->find("���2");

			//�����ġ �����ϱ�
			bg->setPosition(0, 0);
		}

		///////������ ������ ���¸�..������ �ʱ� ��ġ�� �̵���Ŵ//////
		if (bossSpawned == true)
		{
			/////���� ������Ʈ ã��//////
			GameObject * boss = GameObjectPool::instance()->find("����");

			/////���� ����ġ �Ÿ����ϱ�///
			float dist = 600 - boss->getX();  //���� ��ġ - ������ġ = �̵��Ÿ�
			boss->translate(dist, 0);
		}

		//�÷��̾� ������
		GameObjectPool::instance()->addGameObject(new Player(100, 50), 2);

		//[3]�÷��� ü�� �ʱ�ȭ �ϱ�
		hp = 100;
		printHP();
	}
	else {
		//printf("���� ����\n");
		GameObjectPool::instance()->addGameObject(new Gameover(230, 10), 3);
	}
}

void GameManager::bossSpawn()
{
	bossSpawned = true;

	GameObjectPool::instance()->addGameObject(new Boss(600, 105), 2);
}