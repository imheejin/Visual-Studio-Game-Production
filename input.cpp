#include "stdafx.h"
#include "input.h"

//////////////키보드 상태..정의하기////////////////
#define KEY_UP_REP   0 //키가 놓여 있는 상태
#define KEY_DOWN     1 //키가 놓임=>눌림 변경 상태
#define KEY_DOWN_REP 2 //키가 눌려 있는 상태
#define KEY_UP       3 //키가 눌림=>놓임 변경 상태   

/////////////////모든 키보드의 키에 대해서...상태를 저장하기 위한 배열을 만듬////////////////
int state[255]; //KEY_UP_RE[-계속 놓임, KEY_DOWN-놓임=>눌림, KEY_DOWN_REP-계속 눌림, KEY_UP-눌림=>놓임

//////////////////////마우스 좌표 저장..구조체 변수///////////////////////////////////////
MousePosition mousePosition = { 0,0 };

void initInput()  //키입력 초기화 함수
{
    /////////////////키보드 상태 배열을 ..초기화함//////////////////////////
    for (int i = 0; i < 255; i++)
    {
        state[i] = KEY_UP_REP;
    }
}

void updateInput()//키보드를 읽어와서..상태를 변경(업데이트)하는 함수
{
    int key;

    for (int i = 1; i < 255; i++)  //i는 입력을 검사는 키번호이고..키의 상태를 저장하는 배열이 인덱스
    {
        /////////게임사용 키입력하기////////////////
        key = GetAsyncKeyState(i);  //마우스 왼쪽 버튼 검사

        if (state[i] == KEY_UP_REP)  //키가 놓여진 상태
        {
            if ((key & 0x00008000) != 0) //키가 눌림
            {
                ////printf("키가 놓음=>눌림 상태로 가야함\n");
                state[i] = KEY_DOWN; //놓임==>눌림 상태로 감
            }
            else { //키가 눌리지 않음
                state[i] = KEY_UP_REP;
            }
        }
        else if (state[i] == KEY_DOWN) {  //키가 놓임=>눌림을 변경됨

            if ((key & 0x00008000) != 0)  //키가 눌림
            {
                ////printf("키가 계속 눌림 상태로 가야함\n");
                state[i] = KEY_DOWN_REP;
            }
            else { //키가 눌리지 않음

                //printf("키가 눌림=>놓임 상태로 가야함\n");
                state[i] = KEY_UP;
            }
        }
        else if (state[i] == KEY_DOWN_REP) {  //키가 계속 눌림으로..변경됨

            if ((key & 0x00008000) != 0)  //키가 눌림
            {
                ////printf("키가 계속 눌리고 있음\n");
                state[i] = KEY_DOWN_REP;
            }
            else {  //키가 놓임
                ////printf("키가 눌림=>놓임 상태로 가야함\n");
                state[i] = KEY_UP;
            }
        }
        else if (state[i] == KEY_UP) {  //키가 눌림==>놓임으로 .. 변경됨

            if ((key & 0x00008000) != 0)  //키가 눌림
            {
                ////printf("키가 놓임==>눌임 상태로..가야함\n");
                state[i] = KEY_DOWN;
            }
            else {
                /////printf("키가 계속 놓임 .. 상태로 가야함\n");
                state[i] = KEY_UP_REP;
            }
        }
    }
}

void exitInput() //키 입력 종료 함수
{
    //현재는..작성할 코드가 없음
}

////////키입력 알아오기..함수//////////////
//(1)키가..눌림으로..변경되었는지를 알아오는 함수
bool getKeyDown(int keyCode)  //keyCode(가상키 번호)에 해당하는..키가 눌림으로..변경되었는지를 반환함
{
    if (state[keyCode] == KEY_DOWN)
    {
        return true;
    }
    else {
        return false;
    }
}

//(2)키가..놓임 ...변경되었는지를 알아오는 함수
bool getKeyUp(int keyCode)
{
    if (state[keyCode] == KEY_UP)
    {
        return true;
    }
    else {
        return false;
    }
}

//(3)키가..계속해서..눌려지고 있는지를 알아오는 함수
bool getKey(int keyCode)
{
    if (state[keyCode] == KEY_DOWN || state[keyCode] == KEY_DOWN_REP)
    {
        return true;
    }
    else {
        return false;
    }
}

//////마우스 입력 알아오기 함수////////////
bool getMouseButtonDown(int button)  //button : 0-왼쪽 버튼, 1-오른쪽 버튼, 2-가운데 버튼
{
	if (button == 0)
	{
		if (state[VK_LBUTTON] == KEY_DOWN)
		{
			return true;
		}
	
	}
	else if (button == 1)
	{
		if (state[VK_RBUTTON] == KEY_DOWN)
		{
			return true;
		}
	}
	else if (button == 2) 
	{
		if (state[VK_MBUTTON] == KEY_DOWN)
		{
			return true;
		}
	}

	return false;
}

bool getMouseButtonUp(int button)
{
	if (button == 0)
	{
		if (state[VK_LBUTTON] == KEY_UP)
		{
			return true;
		}

	}
	else if (button == 1)
	{
		if (state[VK_RBUTTON] == KEY_UP)
		{
			return true;
		}
	}
	else if (button == 2)
	{
		if (state[VK_MBUTTON] == KEY_UP)
		{
			return true;
		}
	}

	return false;
}

bool getMouseButton(int button)
{
	if (button == 0)
	{
		if (state[VK_LBUTTON] == KEY_DOWN || state[VK_LBUTTON] == KEY_DOWN_REP)
		{
			return true;
		}

	}
	else if (button == 1)
	{
		if (state[VK_RBUTTON] == KEY_DOWN || state[VK_RBUTTON] == KEY_DOWN_REP)
		{
			return true;
		}
	}
	else if (button == 2)
	{
		if (state[VK_MBUTTON] == KEY_DOWN || state[VK_MBUTTON] == KEY_DOWN_REP)
		{
			return true;
		}
	}

	return false;
}

void setMousePosition(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
}

MousePosition getMousePosition()
{
	return mousePosition;
}