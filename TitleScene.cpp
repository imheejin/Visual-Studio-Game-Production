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
	
	pool->addGameObject(new TitleBG(0, 0), 0);  //배경 추가

	/////////////////배경 사운드 추가하기//////////
	Sound * bgm = new Sound();

	bgm->play("asset/BGM/Main.mp3", true);
	//bgm->setLifeTime(5);  //라이프 타임 테스트
	pool->addGameObject(bgm, 0);

	////////////////////UI 버튼 추가하기///////////////////
	pool->addGameObject(new StartButton(100, 150), 1);
	pool->addGameObject(new ExitButton (200, 150), 1);
}