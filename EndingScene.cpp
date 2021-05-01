#include "stdafx.h"
#include "EndingScene.h"
#include "EndingBG.h"
#include "GameObjectPool.h"

EndingScene::EndingScene() : Scene()
{}

EndingScene::~EndingScene()
{}

void EndingScene::init()
{
	GameObjectPool::instance()->addGameObject(new EndingBG(0, 0), 0);
}