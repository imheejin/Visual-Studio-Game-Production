#include "stdafx.h"
#include "Animation.h"
#include "timer.h"

Animation::Animation(const char *name, int tag, bool state, float px, float py)
	      :GameObject(name, tag, state, px, py)
{
	frameNum = 0;  //출력할 애니메이션 이미지 번호

	frameDelay = 0.1;  //기본 한 장면이 보여지는 시간
	frameTimer = 0;    //애니메이션 타이머
	aniId      = 0;    //애니메이션 아이디
	hFlip	  = false; //초기설정은 플립 안함
}

Animation::~Animation()
{
	for (int id = 0; id < MAX_ANI; id++)
	{
		for (int i = 0; i < frame[id].size(); i++)
		{
			delete[] frame[id][i].argb;
			frame[id][i].argb = NULL;

			///////////frame[id][i] 에 달려있는 충돌체 제거하기/////////
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

		drawBmpHFlip(px, py, &frame[aniId][frameNum]);  //좌우 플립 이미지 출력 함수
	}

	if (frameTimer >= frameDelay)
	{
		frameNum++;

		if (frameNum >= frame[aniId].size())  //마지막 이미지에서..처음 이미지로 돌리기
		{
			frameNum = 0;
		}

		//////바뀐 애니메이션 아이디와,  장면 번호를 전달하는 함수//////
		OnFrameChange(aniId, frameNum);

		frameTimer = 0; //애니메이션 타이머..리셋
	}

	///////////스프라이트에..추가된 충돌체 출력하기///////
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
		aniId = id; //[1]출력 애니메이션 아이디 변경
		frameNum = 0;  //[2]애니메이션 이미지를 0 번 부터 시작
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

	/////////애니메이션...스프라이트 안에 추가된...충돌체 이동 시키기///////////
	for (int id = 0; id < MAX_ANI; id++)  //애니메이션 배열 갯수
	{
		for (int i = 0; i < frame[id].size(); i++) //각 배열(stl vector)에 추가된 스프라이트 갯수
		{
			for (int c = 0; c < frame[id][i].cols.size(); c++) //각 스프라이트에 추가된 충돌체 갯수
			{
				frame[id][i].cols[c]->setOwnerPos(px, py);
			}
		}
	}

	///////////자식도 이동시킴/////////////
	for (int i = 0; i < objs.size(); i++)
	{
		objs[i]->translate(dx, dy);
	}
}

int Animation::getFrameNum()
{
	return frameNum;  //현재 출력중이 스프라이트 번호
}

void Animation::OnFrameChange(int id, int frameNum)
{
}