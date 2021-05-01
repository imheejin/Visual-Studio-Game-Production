#pragma once

#include <vector>
#include "GameObject.h"
#include "bmp.h"

#define MAX_ANI 64  //�ִ� �ִϸ��̼� ����

class Animation : public GameObject
{
protected:

	std::vector<Sprite> frame[64];

	////////����� frame ��ȣ////////
	int frameNum;

	///////����� �ִϸ��̼� id//////
	int aniId;

	////////�ִϸ��̼� �ð�//////////
	float frameDelay;  //�� ����� �������� �ð�
	float frameTimer;  //�ִϸ��̼� Ÿ�̸�

	////////��������Ʈ �ø� ���� ����////////
	bool hFlip;  //true-HFlip, false - �ø� ����

public:

	Animation(const char *name, int tag, bool state, float px, float py);
	~Animation();

	////////�ִϸ��̼� ������ �߰� �Լ�/////////
	void addFrame(Sprite sprite, int id);

	/////////////�ִϸ��̼� ����ϱ�////////////
	void draw();

	//////////////�ִϸ��̼� �ð� ����//////////
	void setFrameDelay(float delay);

	//////////////�ִϸ��̼� �����ϱ�///////////
	void play(int id);

	//////�浹ü �������� �Լ� �������̵�//////
	std::vector<AABB *> * getCols();

	//////Translate �������̵�///////////////
	void translate(float dx, float dy);

	//////���� ������� ��Ʈ����Ʈ ��ȣ ��ȯ �Լ�//////
	int getFrameNum();

	/////�ִϸ��̼� ����� ����Ǿ����� �˷��ִ� �̺�Ʈ/////
	virtual void OnFrameChange(int id, int frameNum);
};