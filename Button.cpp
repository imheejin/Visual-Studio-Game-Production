#include "stdafx.h"
#include "Button.h"
#include "Label.h"
#include "input.h"
#include "graphic.h"
#include "timer.h"

Button::Button(const WCHAR * text, float px, float py) : SpriteObject("��ư", 6, true, px, py)
{	
	wcscpy_s(this->text, text);  //��ư �ؽ�Ʈ ����
	
	this->state = normal;        //��ư �⺻ ���� 
	this->delay = 0.5;           //0.5�� Ŭ�� ����
}

Button::~Button()
{
}

void Button::init()
{
	//��ư �̹����ε� �ϱ�
	readBmp("asset/button.bmp", &sprite);

	//��ư �ؽ�Ʈ �߰��ϱ�
	const char * ttf = "asset/ttf/godoMaum.ttf";
	label = new Label(text, ttf, 30, 0x00ffffff, 14, 30);

	addChildObj(label , 2);
}

void Button::update()
{
	if (state == normal)
	{
		//////UI ��ư ������..���콺 ���� ��ư�� ���ȴ����� �˻���
		if (getMouseButtonDown(0) == true)
		{
			///////////////���콺 ��ǥ///////////////
			MousePosition mouse = getMousePosition();

			/////////////UI ��ư �簢�� ����/////////
			float x0, y0, x1, y1;

			x0 = px;
			y0 = py;

			x1 = x0 + sprite.width;
			y1 = y0 + sprite.height;

			if (x0 < mouse.x && mouse.x < x1 && y0 < mouse.y && mouse.y < y1)
			{
				label->translate(2, 2);  //��ư ���� ȿ��
				state = pressed;	     //��ư ���� ����			  
			}
		}
	}
	else if (state == pressed) {

		if (getMouseButtonUp(0) == true)
		{
			label->translate(-2, -2);  //��ư ���� ȿ��
			state = click;			   //��ư�� ���� ����
		}

	}
	else if (state == click) {

		////////Ŭ�� ����////////
		//Sleep(500);

		delay = delay - getDelteTime();

		if (delay < 0)
		{
			OnClick();

			state = normal;   //��ư�� ���¸� �ٽ�..ó������..�ʱ�ȭ��
			delay = 0.5;      //Ŭ�� delay �ʱⰪ ����
		}
	}
}

void Button::OnClick()
{
}

void Button::draw()
{
	///////�θ� SpriteObject�� draw �����ϱ�//////
	SpriteObject::draw();

	/////////////UI ��ư ���� �׸���//////////////
	float x0, y0, x1, y1;

	x0 = px;
	y0 = py;

	x1 = x0 + sprite.width;
	y1 = y0 + sprite.height;

	drawRect(x0, y0, x1, y1, 0, 255, 0);
}