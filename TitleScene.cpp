#include "stdafx.h"
#include "TitleScene.h"
#include "GameObjectPool.h"
#include "TitleBG.h"
#include "StartButton.h"
#include "ExitButton.h"
#include "Sound.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::init()
{
	GameObjectPool * pool = GameObjectPool::instance();
	
	pool->addGameObject(new TitleBG(0, 0), 0);  //��� �߰�

	/////////////////��� ���� �߰��ϱ�//////////
	Sound * bgm = new Sound();

	bgm->play("asset/BGM/Main.mp3", true);
	//bgm->setLifeTime(5);  //������ Ÿ�� �׽�Ʈ
	pool->addGameObject(bgm, 0);

	////////////////////UI ��ư �߰��ϱ�///////////////////
	pool->addGameObject(new StartButton(100, 150), 1);
	pool->addGameObject(new ExitButton (200, 150), 1);
}