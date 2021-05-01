#include "stdafx.h"
#include "GameScene.h"
#include "timer.h"
#include "input.h"
#include "GameBG1.h"
#include "GameBG2.h"
#include "GameObjectPool.h"
#include "Player.h"
#include "Label.h"
#include "FlyingLabel.h"
#include "GameManager.h"
#include "Boss.h"
#include "BossFx.h"
#include "Sound.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::init()
{
	GameObjectPool * pool=GameObjectPool::instance();

	///////////게임매니저..풀에 추가하기//////////////
	GameManager * manager = GameManager::instance();

	pool->addGameObject(manager, 0);
	pool->addGameObject(new GameBG2(0, 0), 1);
	pool->addGameObject(new GameBG1(0, 0), 0);

	pool->addGameObject(new Player (100, 50), 2);

	/////////////////배경 사운드 추가하기//////////
	Sound * bgm = new Sound();

	bgm->play("asset/BGM/Play.mp3", true);
	pool->addGameObject(bgm, 0);
}