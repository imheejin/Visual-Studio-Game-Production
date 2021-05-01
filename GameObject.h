#pragma once

#include <vector>
#include "AABB.h"

class GameObject
{
protected:
	/////////기본정보/////////
	char name[32];
	int  tag;
	bool state;

	///////부모 게임 오브젝트..포인터 저장하기////
	GameObject * parentObj;

	/////////게임오브젝트 alive 상태 정보/////////
	bool alive;   //true - 살아있음, false - 죽었음 (삭제대상)

	/////트랜스폼 - 위치, 회전, 스케일/////
	float px, py; //position

	////////충돌체 - AABB추가하시//////////
	std::vector<AABB *> cols;

	///////////(자식)게임 오브젝트 추가하기///
	std::vector<GameObject *> objs;  

public:
	/////////생성자, 소멸자//////////
	GameObject(const char *name, int tag, bool state, float px, float py);
	virtual ~GameObject();

	/////////기본 활용메소드-가상함수///////
	virtual void init();
	virtual void update();
	virtual void draw();

	/////////////게터, 세터////////////////
	char * getName();
	int    getTag();

	void   setAlive(bool alive);
	bool   getAlive();

	void setSate(bool state);
	bool getState();

	void setParentObj(GameObject * parentObj);

	float getX();  //객체의 현재 x-좌표 구하기
	float getY();  //객체의 현테 y-좌표 구하기

	/////////기타 필요한 메소드 추가////////
	virtual void translate(float dx, float dy);
	void setPosition(float x, float y);

	void addCollider(AABB * aabb);
	void delCollider(int id);

	void addChildObj(GameObject * o, int order);
	void delChildObj(GameObject * o);

	/////////충돌체 한개(임시)가져오기///////
	virtual std::vector<AABB *> * getCols();  //애니메이션 클래스에서는 getCols을 오버라이딩 함

	/////////충돌 이벤트 전달하기////////////
	virtual void OnCollisionEnter(GameObject *obj, AABB * otherCol, AABB * myCol); //충돌이 시작됨
	virtual void OnCollision(GameObject *obj, AABB * otherCol, AABB * myCol);      //충돌이 계속됨
	virtual void OnCollisionExit(GameObject *obj, AABB * otherCol, AABB * myCol);  //충돌이 끝났음

	////////부모 객체가 있는 경우..부모의 좌표를 기준으로..위치 가져오기 메소드/////
	float getXFromParent();
	float getYFromParent();
};