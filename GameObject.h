#pragma once

#include <vector>
#include "AABB.h"

class GameObject
{
protected:
	/////////�⺻����/////////
	char name[32];
	int  tag;
	bool state;

	///////�θ� ���� ������Ʈ..������ �����ϱ�////
	GameObject * parentObj;

	/////////���ӿ�����Ʈ alive ���� ����/////////
	bool alive;   //true - �������, false - �׾��� (�������)

	/////Ʈ������ - ��ġ, ȸ��, ������/////
	float px, py; //position

	////////�浹ü - AABB�߰��Ͻ�//////////
	std::vector<AABB *> cols;

	///////////(�ڽ�)���� ������Ʈ �߰��ϱ�///
	std::vector<GameObject *> objs;  

public:
	/////////������, �Ҹ���//////////
	GameObject(const char *name, int tag, bool state, float px, float py);
	virtual ~GameObject();

	/////////�⺻ Ȱ��޼ҵ�-�����Լ�///////
	virtual void init();
	virtual void update();
	virtual void draw();

	/////////////����, ����////////////////
	char * getName();
	int    getTag();

	void   setAlive(bool alive);
	bool   getAlive();

	void setSate(bool state);
	bool getState();

	void setParentObj(GameObject * parentObj);

	float getX();  //��ü�� ���� x-��ǥ ���ϱ�
	float getY();  //��ü�� ���� y-��ǥ ���ϱ�

	/////////��Ÿ �ʿ��� �޼ҵ� �߰�////////
	virtual void translate(float dx, float dy);
	void setPosition(float x, float y);

	void addCollider(AABB * aabb);
	void delCollider(int id);

	void addChildObj(GameObject * o, int order);
	void delChildObj(GameObject * o);

	/////////�浹ü �Ѱ�(�ӽ�)��������///////
	virtual std::vector<AABB *> * getCols();  //�ִϸ��̼� Ŭ���������� getCols�� �������̵� ��

	/////////�浹 �̺�Ʈ �����ϱ�////////////
	virtual void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol); //�浹�� ���۵�
	virtual void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);      //�浹�� ��ӵ�
	virtual void OnCollisionExit(GameObject *obj, AABB * otherCol, AABB * myCol);  //�浹�� ������

	////////�θ� ��ü�� �ִ� ���..�θ��� ��ǥ�� ��������..��ġ �������� �޼ҵ�/////
	float getXFromParent();
	float getYFromParent();
};