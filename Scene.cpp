#include "stdafx.h"
#include "Scene.h"
#include "GameObjectPool.h"

Scene::Scene()
{}

Scene::~Scene()
{}

void Scene::init()   //�������� �ε� �� �ʱ�ȭ
{
}

void Scene::update() //���� ������Ʈ ������Ʈ
{
	GameObjectPool * pool = GameObjectPool::instance();

	pool->update();
}

void Scene::checkCol()
{
	GameObjectPool * pool = GameObjectPool::instance();

	pool->checkCol();
}

void Scene::removeDeadObj() //���� ���ӿ�����Ʈ �����ϱ� 
{
	GameObjectPool * pool = GameObjectPool::instance();

	pool->removeDeadObj();
}

void Scene::draw()   //���� ������Ʈ ����ϱ�
{
	GameObjectPool * pool = GameObjectPool::instance();

	pool->draw();
}

void Scene::exit()   //�������� ����
{
	GameObjectPool * pool = GameObjectPool::instance();

	pool->clear();
}