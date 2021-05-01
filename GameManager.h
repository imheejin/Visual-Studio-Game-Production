#pragma once

#include "GameObject.h"
#include "Label.h"
#include "Bar.h"

#define MAX_GAMES 5

class GameManager : public GameObject
{
private:

	////////생성자, 소멸자///////
	GameManager();
	~GameManager();

	////////싱글톤 객체..저장포인터///////
	static GameManager * manager;

	////////남은 겜임수 표시 아이콘 객체 배열/////////
	GameObject * icons[MAX_GAMES];
	int games;     

	//////////////획득점수 변수//////////////////////
	int score;
	Label * scoreLabel;

	/////////////플레이어 체력 변수//////////////////
	int hp;
	Label * hpLabel;
	Bar   * hpBar;

	//////////////보스 스폰 정보 변수///////////////
	bool bossSpawned;

public:

	////////싱글톤 객체(인스턴스) 가져오기 메소드////
	static GameManager * instance();

	//////////////init 오버로딩////////////////
	void init();

	/////////////점수 획득 메소드///////////////
	void addScore(int point);
	void printScore();

	////////////체력 감소/증가 메소드////////////
	void addHP(int point);
	void printHP();

	/////////////현재 체력 게터//////////////////
	int getHP();

	//////////////플레이어 리스폰 메소드/////////
	void playerSpawn();

	///////////////보스 스폰 메소드/////////////
	void bossSpawn();
};
