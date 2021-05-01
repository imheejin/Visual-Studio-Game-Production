#pragma once

#include "GameObject.h"
#include "Label.h"
#include "Bar.h"

#define MAX_GAMES 5

class GameManager : public GameObject
{
private:

	////////������, �Ҹ���///////
	GameManager();
	~GameManager();

	////////�̱��� ��ü..����������///////
	static GameManager * manager;

	////////���� ���Ӽ� ǥ�� ������ ��ü �迭/////////
	GameObject * icons[MAX_GAMES];
	int games;     

	//////////////ȹ������ ����//////////////////////
	int score;
	Label * scoreLabel;

	/////////////�÷��̾� ü�� ����//////////////////
	int hp;
	Label * hpLabel;
	Bar   * hpBar;

	//////////////���� ���� ���� ����///////////////
	bool bossSpawned;

public:

	////////�̱��� ��ü(�ν��Ͻ�) �������� �޼ҵ�////
	static GameManager * instance();

	//////////////init �����ε�////////////////
	void init();

	/////////////���� ȹ�� �޼ҵ�///////////////
	void addScore(int point);
	void printScore();

	////////////ü�� ����/���� �޼ҵ�////////////
	void addHP(int point);
	void printHP();

	/////////////���� ü�� ����//////////////////
	int getHP();

	//////////////�÷��̾� ������ �޼ҵ�/////////
	void playerSpawn();

	///////////////���� ���� �޼ҵ�/////////////
	void bossSpawn();
};
