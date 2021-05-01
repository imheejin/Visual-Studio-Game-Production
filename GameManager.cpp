#include "stdafx.h"
#include "GameManager.h"
#include "GameObjectPool.h"
#include "Label.h"
#include "Icon.h"
#include "Player.h"
#include "Gameover.h"
#include "Boss.h"

GameManager * GameManager::manager=NULL;

GameManager::GameManager() : GameObject("게임매니저", 6, true, 0,0)
{}

GameManager::~GameManager()
{
	/////////게임 매니저..객체 저장 포인터를 NULL로 지정함///////
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
	
	////////체력/점수 문자 출력하기////////
	const char * ttf = "asset/ttf/godoMaum.ttf";
	
	pool->addGameObject(new Label(L"체력:", ttf , 32, 0x00ffffff, 10, 32), 3);
	pool->addGameObject(new Label(L"점수:", ttf,  32, 0x00ffffff, 10, 65), 3);

	/////////게임수 초기화 하기//////////////
	games = 3;

	/////////남은 게임수 아이콘 만들기///////
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
	
	/////////////점수 변수 초기화//////////////
	score		= 0;
	scoreLabel = new Label(L"0", ttf, 40, 0x000000ff, 66, 65);
	pool->addGameObject(scoreLabel, 3);

	/////////////체력 변수 초기화//////////////
	hp			= 100;

	hpBar = new Bar(70, 10, 150, 20);
	pool->addGameObject(hpBar, 3);

	hpLabel = new Label(L"100", ttf, 32, 0x000000ff, 120, 30);
	pool->addGameObject(hpLabel, 3);

	hpBar->setPosition(1.0f);

	//////////////보스 스폰 변수..초기화////////
	bossSpawned=false;

	////////////개발 정보 출력하기/////////////
	pool->addGameObject(new Label(L"2D 게임 개발 프로젝트 V1.0", ttf, 18, 0x00ffffff, 450, 150), 3);
	pool->addGameObject(new Label(L"개발자: 홍길동", ttf, 18, 0x00ffffff, 450, 165), 3);
	pool->addGameObject(new Label(L"개발기간: 2019년4월~5월", ttf, 18, 0x00ffffff, 450, 180), 3);

	///////////게임종료 테스트 하기////////////
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
	
	///////hp 최대치///////
	if (hp > 100)
	{
		hp = 100;
	}

	//////hp 화면 출력/////
	printHP();
}

int GameManager::getHP()
{
	return hp;
}

void GameManager::printHP()
{
	//////HP를 숫자로 출력//////
	WCHAR temp[32]=L"0";

	if (hp > 0)
	{
		wsprintf(temp, L"%d", hp);
	}

	hpLabel->setText(temp);

	///////HP 프로그레시브바(Progressive Bar)로 출력//////
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
	//[1]게임수 감소
	games--;

	if (games >= 0)
	{
		icons[games]->setSate(false);  //게임수 표시 아이콘 감소

		//[2]플레이어 리스폰 - 배경 위치 리셋
		
		if (bossSpawned == false)  //보스전에서는 배경 리세하지 않음
		{
			//배경을 처음으로 돌리기
			GameObject * bg = GameObjectPool::instance()->find("배경2");

			//배경위치 리셋하기
			bg->setPosition(0, 0);
		}

		///////보스가 스폰된 상태면..보스도 초기 위치로 이동시킴//////
		if (bossSpawned == true)
		{
			/////보스 오브젝트 찾기//////
			GameObject * boss = GameObjectPool::instance()->find("보스");

			/////보스 원위치 거리구하기///
			float dist = 600 - boss->getX();  //원래 위치 - 현재위치 = 이동거리
			boss->translate(dist, 0);
		}

		//플레이어 리스폰
		GameObjectPool::instance()->addGameObject(new Player(100, 50), 2);

		//[3]플레어 체력 초기화 하기
		hp = 100;
		printHP();
	}
	else {
		//printf("게임 오버\n");
		GameObjectPool::instance()->addGameObject(new Gameover(230, 10), 3);
	}
}

void GameManager::bossSpawn()
{
	bossSpawned = true;

	GameObjectPool::instance()->addGameObject(new Boss(600, 105), 2);
}