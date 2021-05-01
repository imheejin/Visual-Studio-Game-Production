#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectPool.h"

GameObject::GameObject(const char *name, int tag, bool state, float px, float py)
{
	strcpy_s(this->name, name);
	this->tag   = tag;
	this->state = state;

	this->px = px;
	this->py = py;

	this->alive     = true;  //ó������ �������
	this->parentObj = NULL;  //ó������ �θ� ������Ʈ�� ����
}

GameObject::~GameObject()
{
	/////////�߰��� �浹ü �����ϱ�/////////
	for (int i = 0; i < cols.size(); i++)
	{
		delete cols[i];
	}

	cols.clear();

	////////�ڽ����� �߰��� ���ӿ�����Ʈ �����ϱ�/////
	for (int i = 0; i < objs.size(); i++)
	{
		delChildObj(objs[i]);
	}
}

/////////�⺻ Ȱ��޼ҵ�-�����Լ�///////
void GameObject::init()
{
}

void GameObject::update()
{
}

void GameObject::draw()
{
	///////�浹ü ����ϱ�///////
	for (int i = 0; i < cols.size(); i++)
	{
		cols[i]->draw();
	}
}

void GameObject::translate(float dx, float dy)
{
	px = px + dx;
	py = py + dy;

	/////////�浹ü �̵� ��Ű��///////////
	for (int i = 0; i < cols.size(); i++)
	{
		cols[i]->setOwnerPos(px, py);		
	}

	///////////�ڽĵ� �̵���Ŵ/////////////
	for (int i = 0; i < objs.size(); i++)
	{
		objs[i]->translate(dx, dy);
	}
}

void GameObject::setPosition(float x, float y)
{
	float dx = x - px;  //x �̵��Ÿ� 
	float dy = y - py;  //y �̵��Ÿ�

	GameObject::translate(dx, dy);  //�������̵� �̿����� �ʰ�..GameObjectŬ������ translate �̿�
}

void GameObject::addCollider(AABB * aabb)
{
	aabb->setOwnerPos(px, py);
	cols.push_back(aabb);
}

void GameObject::delCollider(int id)
{
	for (int i = 0; i < cols.size(); i++)
	{
		if (cols[i]->getId() == id)
		{
			//[1]AABB��ü �����ϱ�
			delete cols[i];

			//[2]stl vector���� ���� �ڸ� �����
			cols.erase(cols.begin() + i);
		}
	}
}

void GameObject::addChildObj(GameObject * o, int order)
{
	objs.push_back(o);
	
	///////�ڽ� ������Ʈ�� GameObjectPool�� �߰��ϱ�//////
	GameObjectPool * pool = GameObjectPool::instance();
	pool->addGameObject(o, order);

	///////�ڽ� ������Ʈ��..�θ� ������Ʈ �����ϱ�//////////
	o->setParentObj(this);
}

void GameObject::delChildObj(GameObject * o)
{
	//[1]�ڽĿ�����Ʈ���� ������
	for (int i = 0; i < objs.size(); i++)
	{
		if (objs[i] == o)
		{
			objs.erase(objs.begin() + i);  //stl vector objs���� i ��° ��ü�� ����
			break;
		}
	}

	//[2]GameObjectPool���� ������Ʈ �����ϱ�
	GameObjectPool * pool = GameObjectPool::instance();
	pool->delGameObject(o);  //Ǯ���� ������Ʈ ���� (delete����)
}

char * GameObject::getName()
{
	return name;
}

int GameObject::getTag()
{
	return tag;
}

void GameObject::setAlive(bool alive)
{
	this->alive = alive;
}

bool GameObject::getAlive()
{
	return alive;
}

float GameObject::getX()
{
	return px;
}

float GameObject::getY()
{
	return py;
}

void GameObject::setSate(bool state)
{
	this->state = state;
}

bool GameObject::getState()
{
	return state;
}

std::vector<AABB *> * GameObject::getCols()
{
	return &cols;  //std::vector<AABB *> cols;
}

void GameObject::OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol)
{
}

void GameObject::OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol)
{
}

void GameObject::OnCollisionExit(GameObject *obj, AABB * otherCol, AABB * myCol)
{
}

void GameObject::setParentObj(GameObject * parentObj)
{
	this->parentObj = parentObj;

	///////////�ڽ� ��ǥ��..�θ� ��ǥ�� ���ؼ�..�ڽ� ��ǥ�� ������/////////
	this->px = this->px + parentObj->px;
	this->py = this->py + parentObj->py;
}

float GameObject::getXFromParent()
{
	//[1] �ڱ���ǥ 
	float x = px;

	//[2]�θ� �ִ����� �˻��� [����]�θ� ��ü ���� �ٽ� �θ� ������..�ݺ������� ��ǥ�� ������
	if (parentObj != NULL)  
	{
		x = x - parentObj->px;
	}

	return x;
}

float GameObject::getYFromParent()
{
	//[1] �ڱ���ǥ 
	float y = py;

	//[2]�θ� �ִ����� �˻��� [����]�θ� ��ü ���� �ٽ� �θ� ������..�ݺ������� ��ǥ�� ������
	if (parentObj != NULL)
	{
		y = y - parentObj->py;
	}

	return y;
}
