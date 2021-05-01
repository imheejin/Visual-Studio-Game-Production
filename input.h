#pragma once

#include <Windows.h>  //input.h�� include�Ǹ鼭..windows.h�� ���� include ��

////////Ű����..���º���..���۽�Ű��////////
void initInput();   //Ű�Է� �ʱ�ȭ �Լ�
void updateInput(); //Ű���带 �о�ͼ�..���¸� ����(������Ʈ)�ϴ� �Լ�
void exitInput();   //Ű�Է� ���� �Լ�

////////Ű�Է� �˾ƿ���..�Լ�//////////////
////�Ʒ��� Ű�Լ��� WM_KEYUP/WM_KEYDOWN�� �̿��ؼ�..������ ���� ����
//(1)Ű��..��������..����Ǿ������� �˾ƿ��� �Լ�
bool getKeyDown(int keyCode);  //keyCode(����Ű ��ȣ)�� �ش��ϴ�..Ű�� ��������..����Ǿ������� ��ȯ��

//(2)Ű��..���� ...����Ǿ������� �˾ƿ��� �Լ�
bool getKeyUp(int keyCode);

//(3)Ű��..����ؼ�..�������� �ִ����� �˾ƿ��� �Լ�
bool getKey(int keyCode);

/////////////���콺 ��ǥ ����ü////////////
struct MousePosition
{
	short x;
	short y;
};

//////���콺 �Է� �˾ƿ��� �Լ�////////////
bool getMouseButtonDown(int button);  //button : 0-���� ��ư, 1-������ ��ư, 2-��� ��ư
bool getMouseButtonUp  (int button);
bool getMouseButton    (int button);

/////���콺 ��ǥ .. �����ϱ�/�������� /////
void setMousePosition(int x, int y);
MousePosition getMousePosition();