#include "stdafx.h"
#include "Button.h"
#include "Label.h"
#include "input.h"
#include "graphic.h"
#include "timer.h"

Button::Button(const WCHAR * text, float px, float py) : SpriteObject("버튼", 6, true, px, py)
{	
	wcscpy_s(this->text, text);  //버튼 텍스트 저장
	
	this->state = normal;        //버튼 기본 상태 
	this->delay = 0.5;           //0.5초 클릭 지연
}

Button::~Button()
{
}

void Button::init()
{
	//버튼 이미지로드 하기
	readBmp("asset/button.bmp", &sprite);

	//버튼 텍스트 추가하기
	const char * ttf = "asset/ttf/godoMaum.ttf";
	label = new Label(text, ttf, 30, 0x00ffffff, 14, 30);

	addChildObj(label , 2);
}

void Button::update()
{
	if (state == normal)
	{
		//////UI 버튼 위에서..마우스 왼쪽 버튼이 눌렸는지를 검사함
		if (getMouseButtonDown(0) == true)
		{
			///////////////마우스 좌표///////////////
			MousePosition mouse = getMousePosition();

			/////////////UI 버튼 사각형 영역/////////
			float x0, y0, x1, y1;

			x0 = px;
			y0 = py;

			x1 = x0 + sprite.width;
			y1 = y0 + sprite.height;

			if (x0 < mouse.x && mouse.x < x1 && y0 < mouse.y && mouse.y < y1)
			{
				label->translate(2, 2);  //버튼 눌림 효과
				state = pressed;	     //버튼 상태 변경			  
			}
		}
	}
	else if (state == pressed) {

		if (getMouseButtonUp(0) == true)
		{
			label->translate(-2, -2);  //버튼 놓임 효과
			state = click;			   //버튼의 상태 변경
		}

	}
	else if (state == click) {

		////////클릭 지연////////
		//Sleep(500);

		delay = delay - getDelteTime();

		if (delay < 0)
		{
			OnClick();

			state = normal;   //버튼의 상태를 다시..처음으로..초기화함
			delay = 0.5;      //클릭 delay 초기값 복원
		}
	}
}

void Button::OnClick()
{
}

void Button::draw()
{
	///////부모 SpriteObject의 draw 실행하기//////
	SpriteObject::draw();

	/////////////UI 버튼 영역 그리기//////////////
	float x0, y0, x1, y1;

	x0 = px;
	y0 = py;

	x1 = x0 + sprite.width;
	y1 = y0 + sprite.height;

	drawRect(x0, y0, x1, y1, 0, 255, 0);
}