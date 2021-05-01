#include "stdafx.h"
#include "timer.h"

float prevTime =0;  //이전장면의 시작 시간
float currTime =0;  //현재장면의 시작 시간
float deltaTime=0;

////////타이머..구동시키기///////////
void initTimer()
{
    /////////DeltaTime(델타타임) - 장면간에 걸리는 시간(초) 변수/////
    prevTime = (float)GetTickCount() / 1000;  //이전장면의 시작 시간
    currTime = (float)GetTickCount() / 1000;  //현재장면의 시작 시간
    deltaTime;
}

void updateTimer()
{
    ////////현재 시간을 구구함/////////////
    currTime = (float)GetTickCount() / 1000;
    deltaTime = currTime - prevTime;   //현재 장면 시간 - 이전 장면 시간
    prevTime = currTime;              //현재 장면의 시간은 ... 다음 장면의 이전 시간이 됨
}

void exitTimer()
{
    //타이머..종료는 작성 코드 없음
}

////////델타타임..가져오기 함수////////
float getDelteTime()
{
    return deltaTime;
}