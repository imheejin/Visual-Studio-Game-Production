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

	this->alive     = true;  //처음에는 살아있음
	this->parentObj = NULL;  //처음에는 부모 오브젝트가 없음
}

GameObject::~GameObject()
{
	/////////추가한 충돌체 제거하기/////////
	for (int i = 0; i < cols.size(); i++)
	{
		delete cols[i];
	}

	cols.clear();

	////////자식으로 추가된 게임오브젝트 제거하기/////
	for (int i = 0; i < objs.size(); i++)
	{
		delChildObj(objs[i]);
	}
}

/////////기본 활용메소드-가상함수///////
void GameObject::init()
{
}

void GameObject::update()
{
}

void GameObject::draw()
{
	///////충돌체 출력하기///////
	for (int i = 0; i < cols.size(); i++)
	{
		cols[i]->draw();
	}
}

void GameObject::translate(float dx, float dy)
{
	px = px + dx;
	py = py + dy;

	/////////충돌체 이동 시키기///////////
	for (int i = 0; i < cols.size(); i++)
	{
		cols[i]->setOwnerPos(px, py);		
	}

	///////////자식도 이동시킴/////////////
	for (int i = 0; i < objs.size(); i++)
	{
		objs[i]->translate(dx, dy);
	}
}

void GameObject::setPosition(float x, float y)
{
	float dx = x - px;  //x 이동거리 
	float dy = y - py;  //y 이동거리

	GameObject::translate(dx, dy);  //오버라이딩 이용하지 않고..GameObject클래스의 translate 이용
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
			//[1]AABB객체 삭제하기
			delete cols[i];

			//[2]stl vector에서 저장 자리 지우기
			cols.erase(cols.begin() + i);
		}
	}
}

void GameObject::addChildObj(GameObject * o, int order)
{
	objs.push_back(o);
	
	///////자식 오브젝트를 GameObjectPool에 추가하기//////
	GameObjectPool * pool = GameObjectPool::instance();
	pool->addGameObject(o, order);

	///////자식 오브젝트에..부모 오브젝트 지정하기//////////
	o->setParentObj(this);
}

void GameObject::delChildObj(GameObject * o)
{
	//[1]자식오브젝트에서 빼내기
	for (int i = 0; i < objs.size(); i++)
	{
		if (objs[i] == o)
		{
			objs.erase(objs.begin() + i);  //stl vector objs에서 i 번째 객체를 빼냄
			break;
		}
	}

	//[2]GameObjectPool에서 오브젝트 제거하기
	GameObjectPool * pool = GameObjectPool::instance();
	pool->delGameObject(o);  //풀에서 오브젝트 제거 (delete까지)
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

	///////////자식 좌표에..부모 좌표를 더해서..자식 좌표를 보정함/////////
	this->px = this->px + parentObj->px;
	this->py = this->py + parentObj->py;
}

float GameObject::getXFromParent()
{
	//[1] 자기좌표 
	float x = px;

	//[2]부모가 있는지를 검사함 [참고]부모 객체 위에 다시 부모가 있으면..반복적으로 좌표에 적용함
	if (parentObj != NULL)  
	{
		x = x - parentObj->px;
	}

	return x;
}

float GameObject::getYFromParent()
{
	//[1] 자기좌표 
	float y = py;

	//[2]부모가 있는지를 검사함 [참고]부모 객체 위에 다시 부모가 있으면..반복적으로 좌표에 적용함
	if (parentObj != NULL)
	{
		y = y - parentObj->py;
	}

	return y;
}
