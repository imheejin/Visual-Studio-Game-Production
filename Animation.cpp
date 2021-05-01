#include "stdafx.h"
#include "Animation.h"
#include "timer.h"

Animation::Animation(const char *name, int tag, bool state, float px, float py)
	      :GameObject(name, tag, state, px, py)
{
	frameNum = 0;  //����� �ִϸ��̼� �̹��� ��ȣ

	frameDelay = 0.1;  //�⺻ �� ����� �������� �ð�
	frameTimer = 0;    //�ִϸ��̼� Ÿ�̸�
	aniId      = 0;    //�ִϸ��̼� ���̵�
	hFlip	  = false; //�ʱ⼳���� �ø� ����
}

Animation::~Animation()
{
	for (int id = 0; id < MAX_ANI; id++)
	{
		for (int i = 0; i < frame[id].size(); i++)
		{
			delete[] frame[id][i].argb;
			frame[id][i].argb = NULL;

			///////////frame[id][i] �� �޷��ִ� �浹ü �����ϱ�/////////
			for (int k = 0; k < frame[id][i].cols.size(); k++)
			{
				delete frame[id][i].cols[k];
			}
				frame[id][i].cols.clear();
		}
	}
}

void Animation::addFrame(Sprite sprite, int id)
{
	frame[id].push_back(sprite);
}

void Animation::draw()
{
	frameTimer = frameTimer + getDelteTime();

	if (hFlip != true)
	{
		drawBmp(px, py, &frame[aniId][frameNum]); 
	}
	else {

		drawBmpHFlip(px, py, &frame[aniId][frameNum]);  //�¿� �ø� �̹��� ��� �Լ�
	}

	if (frameTimer >= frameDelay)
	{
		frameNum++;

		if (frameNum >= frame[aniId].size())  //������ �̹�������..ó�� �̹����� ������
		{
			frameNum = 0;
		}

		//////�ٲ� �ִϸ��̼� ���̵��,  ��� ��ȣ�� �����ϴ� �Լ�//////
		OnFrameChange(aniId, frameNum);

		frameTimer = 0; //�ִϸ��̼� Ÿ�̸�..����
	}

	///////////��������Ʈ��..�߰��� �浹ü ����ϱ�///////
	frame[aniId][frameNum].draw();

}

void Animation::setFrameDelay(float delay)
{
	frameDelay = delay;
}

void Animation::play(int id)
{	
	if (aniId != id)
	{
		aniId = id; //[1]��� �ִϸ��̼� ���̵� ����
		frameNum = 0;  //[2]�ִϸ��̼� �̹����� 0 �� ���� ����
	}
}

std::vector<AABB *> * Animation::getCols()
{
	return &frame[aniId][frameNum].cols;
}

void Animation::translate(float dx, float dy)
{
	px = px + dx;
	py = py + dy;

	/////////�ִϸ��̼�...��������Ʈ �ȿ� �߰���...�浹ü �̵� ��Ű��///////////
	for (int id = 0; id < MAX_ANI; id++)  //�ִϸ��̼� �迭 ����
	{
		for (int i = 0; i < frame[id].size(); i++) //�� �迭(stl vector)�� �߰��� ��������Ʈ ����
		{
			for (int c = 0; c < frame[id][i].cols.size(); c++) //�� ��������Ʈ�� �߰��� �浹ü ����
			{
				frame[id][i].cols[c]->setOwnerPos(px, py);
			}
		}
	}

	///////////�ڽĵ� �̵���Ŵ/////////////
	for (int i = 0; i < objs.size(); i++)
	{
		objs[i]->translate(dx, dy);
	}
}

int Animation::getFrameNum()
{
	return frameNum;  //���� ������� ��������Ʈ ��ȣ
}

void Animation::OnFrameChange(int id, int frameNum)
{
}