#pragma once

#include <Windows.h>  //input.h가 include되면서..windows.h도 같이 include 됨

////////키보드..상태변경..동작시키기////////
void initInput();   //키입력 초기화 함수
void updateInput(); //키보드를 읽어와서..상태를 변경(업데이트)하는 함수
void exitInput();   //키입력 종료 함수

////////키입력 알아오기..함수//////////////
////아래의 키함수는 WM_KEYUP/WM_KEYDOWN을 이용해서..구현할 수도 있음
//(1)키가..눌림으로..변경되었는지를 알아오는 함수
bool getKeyDown(int keyCode);  //keyCode(가상키 번호)에 해당하는..키가 눌림으로..변경되었는지를 반환함

//(2)키가..놓임 ...변경되었는지를 알아오는 함수
bool getKeyUp(int keyCode);

//(3)키가..계속해서..눌려지고 있는지를 알아오는 함수
bool getKey(int keyCode);

/////////////마우스 좌표 구조체////////////
struct MousePosition
{
	short x;
	short y;
};

//////마우스 입력 알아오기 함수////////////
bool getMouseButtonDown(int button);  //button : 0-왼쪽 버튼, 1-오른쪽 버튼, 2-가운데 버튼
bool getMouseButtonUp  (int button);
bool getMouseButton    (int button);

/////마우스 좌표 .. 저장하기/가져오기 /////
void setMousePosition(int x, int y);
MousePosition getMousePosition();