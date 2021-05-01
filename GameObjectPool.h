#pragma once

#include <vector>
#include "GameObject.h"
#include "ColPair.h"

#define MAX_LAYERS 8

class GameObjectPool
{
private:

	static GameObjectPool * pool;

	////////���ӿ�����Ʈ ���� stl vector////////
	std::vector<GameObject *> objs[MAX_LAYERS];  //MAX_LAYERS�� ��ϰ��� - ���̾� ����

	/////////�浹�� ������ �����ϴ� stl vector//////
	std::vector<ColPair *> cols;

	GameObjectPool();
	virtual ~GameObjectPool();
public:

	static GameObjectPool * instance();

	///////////���� ��ü �߰��ϱ�///////////
	void addGameObject(GameObject * o, int order);

	///////////���� ��ü �����ϱ�///////////
	void delGameObject(GameObject *o);

	///////////���� ���ӿ�����Ʈ ��� �����ϱ�/////
	void removeDeadObj();

	//////�߰��� ���ӿ�����Ʈ ������Ʈ�ϱ�////
	void update();

	///////�߰��� ���ӿ�����Ʈ ����ϱ�///////
	void draw();

	////////���ӿ�����Ʈ���� �浹üũ�ϱ�//////
	void checkCol();
	void checkColSameLayer(int layer);  //���� ���̾ �ִ� ������Ʈ �浹�˻�
	void checkColDiffLayer(int layer1, int layer2);  //�ٸ� ���̾ �ִ� ������Ʈ �浹�˻�

	/////////////��ü ã�� �޼ҵ�////////////
	GameObject * find(const char * name);

	///////////�浹ü �߰��ϱ� �Լ�-������ �浹�� ���� ��������..�߰��ϴ� �Լ�////////
	void pushColPair(GameObject * A, AABB * aa, GameObject * B, AABB *ab);

	////////////�浹ü �����Լ� - ����� �浹ü�� �浹���� �ʾ������� ǥ��////////////
	void resetColPair();

	////////////////////�浹�� ���� �浹�� �˻��ϰ�..�����ϱ�////////////////////////
	void popColPair();

	//////////////////���ӿ�����Ʈ Ǯ(pool) ����////////////
	void clear();
};