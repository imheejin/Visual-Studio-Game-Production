#pragma once

#include <vector>
#include "GameObject.h"
#include "ColPair.h"

#define MAX_LAYERS 8

class GameObjectPool
{
private:

	static GameObjectPool * pool;

	////////게임오브젝트 저장 stl vector////////
	std::vector<GameObject *> objs[MAX_LAYERS];  //MAX_LAYERS은 목록갯수 - 레이어 갯수

	/////////충돌쌍 정보를 저장하는 stl vector//////
	std::vector<ColPair *> cols;

	GameObjectPool();
	virtual ~GameObjectPool();
public:

	static GameObjectPool * instance();

	///////////게임 객체 추가하기///////////
	void addGameObject(GameObject * o, int order);

	///////////게임 객체 제거하기///////////
	void delGameObject(GameObject *o);

	///////////죽은 게임오브젝트 모두 제거하기/////
	void removeDeadObj();

	//////추가된 게임오브젝트 업데이트하기////
	void update();

	///////추가된 게임오브젝트 출력하기///////
	void draw();

	////////게임오브젝트간의 충돌체크하기//////
	void checkCol();
	void checkColSameLayer(int layer);  //같은 레이어에 있는 오브젝트 충돌검사
	void checkColDiffLayer(int layer1, int layer2);  //다른 레이어에 있는 오브젝트 충돌검사

	/////////////객체 찾기 메소드////////////
	GameObject * find(const char * name);

	///////////충돌체 추가하기 함수-이전에 충돌한 쌍이 없을때만..추가하는 함수////////
	void pushColPair(GameObject * A, AABB * aa, GameObject * B, AABB *ab);

	////////////충돌체 리셋함수 - 저장된 충돌체를 충돌되지 않았음으로 표시////////////
	void resetColPair();

	////////////////////충돌이 끝난 충돌쌍 검색하고..제거하기////////////////////////
	void popColPair();

	//////////////////게임오브젝트 풀(pool) 비우기////////////
	void clear();
};