#include "stdafx.h"
#include "Scene.h"
#include "GameObjectPool.h"

Scene::Scene()
{}

Scene::~Scene()
{}

void Scene::init()   //스테이지 로드 및 초기화
{
}

void Scene::update() //게임 오브젝트 업데이트
{
	GameObjectPool * pool = GameObjectPool::instance();

	pool->update();
}

void Scene::checkCol()
{
	GameObjectPool * pool = GameObjectPool::instance();

	pool->checkCol();
}

void Scene::removeDeadObj() //죽은 게임오브젝트 삭제하기 
{
	GameObjectPool * pool = GameObjectPool::instance();

	pool->removeDeadObj();
}

void Scene::draw()   //게임 오브젝트 출력하기
{
	GameObjectPool * pool = GameObjectPool::instance();

	pool->draw();
}

void Scene::exit()   //스테이지 제거
{
	GameObjectPool * pool = GameObjectPool::instance();

	pool->clear();
}