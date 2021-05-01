#include "stdafx.h"
#include "input.h"

//////////////Ű���� ����..�����ϱ�////////////////
#define KEY_UP_REP   0 //Ű�� ���� �ִ� ����
#define KEY_DOWN     1 //Ű�� ����=>���� ���� ����
#define KEY_DOWN_REP 2 //Ű�� ���� �ִ� ����
#define KEY_UP       3 //Ű�� ����=>���� ���� ����   

/////////////////��� Ű������ Ű�� ���ؼ�...���¸� �����ϱ� ���� �迭�� ����////////////////
int state[255]; //KEY_UP_RE[-��� ����, KEY_DOWN-����=>����, KEY_DOWN_REP-��� ����, KEY_UP-����=>����

//////////////////////���콺 ��ǥ ����..����ü ����///////////////////////////////////////
MousePosition mousePosition = { 0,0 };

void initInput()  //Ű�Է� �ʱ�ȭ �Լ�
{
    /////////////////Ű���� ���� �迭�� ..�ʱ�ȭ��//////////////////////////
    for (int i = 0; i < 255; i++)
    {
        state[i] = KEY_UP_REP;
    }
}

void updateInput()//Ű���带 �о�ͼ�..���¸� ����(������Ʈ)�ϴ� �Լ�
{
    int key;

    for (int i = 1; i < 255; i++)  //i�� �Է��� �˻�� Ű��ȣ�̰�..Ű�� ���¸� �����ϴ� �迭�� �ε���
    {
        /////////���ӻ�� Ű�Է��ϱ�////////////////
        key = GetAsyncKeyState(i);  //���콺 ���� ��ư �˻�

        if (state[i] == KEY_UP_REP)  //Ű�� ������ ����
        {
            if ((key & 0x00008000) != 0) //Ű�� ����
            {
                ////printf("Ű�� ����=>���� ���·� ������\n");
                state[i] = KEY_DOWN; //����==>���� ���·� ��
            }
            else { //Ű�� ������ ����
                state[i] = KEY_UP_REP;
            }
        }
        else if (state[i] == KEY_DOWN) {  //Ű�� ����=>������ �����

            if ((key & 0x00008000) != 0)  //Ű�� ����
            {
                ////printf("Ű�� ��� ���� ���·� ������\n");
                state[i] = KEY_DOWN_REP;
            }
            else { //Ű�� ������ ����

                //printf("Ű�� ����=>���� ���·� ������\n");
                state[i] = KEY_UP;
            }
        }
        else if (state[i] == KEY_DOWN_REP) {  //Ű�� ��� ��������..�����

            if ((key & 0x00008000) != 0)  //Ű�� ����
            {
                ////printf("Ű�� ��� ������ ����\n");
                state[i] = KEY_DOWN_REP;
            }
            else {  //Ű�� ����
                ////printf("Ű�� ����=>���� ���·� ������\n");
                state[i] = KEY_UP;
            }
        }
        else if (state[i] == KEY_UP) {  //Ű�� ����==>�������� .. �����

            if ((key & 0x00008000) != 0)  //Ű�� ����
            {
                ////printf("Ű�� ����==>���� ���·�..������\n");
                state[i] = KEY_DOWN;
            }
            else {
                /////printf("Ű�� ��� ���� .. ���·� ������\n");
                state[i] = KEY_UP_REP;
            }
        }
    }
}

void exitInput() //Ű �Է� ���� �Լ�
{
    //�����..�ۼ��� �ڵ尡 ����
}

////////Ű�Է� �˾ƿ���..�Լ�//////////////
//(1)Ű��..��������..����Ǿ������� �˾ƿ��� �Լ�
bool getKeyDown(int keyCode)  //keyCode(����Ű ��ȣ)�� �ش��ϴ�..Ű�� ��������..����Ǿ������� ��ȯ��
{
    if (state[keyCode] == KEY_DOWN)
    {
        return true;
    }
    else {
        return false;
    }
}

//(2)Ű��..���� ...����Ǿ������� �˾ƿ��� �Լ�
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

//(3)Ű��..����ؼ�..�������� �ִ����� �˾ƿ��� �Լ�
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

//////���콺 �Է� �˾ƿ��� �Լ�////////////
bool getMouseButtonDown(int button)  //button : 0-���� ��ư, 1-������ ��ư, 2-��� ��ư
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