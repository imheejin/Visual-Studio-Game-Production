#pragma once

#include <Windows.h>
#include "SpriteObject.h"
#include "Label.h"

class Button : public SpriteObject
{
protected:

	enum State{normal, pressed, click};

	State state;    //버튼 상태 저장 변수
	WCHAR text[16]; //버튼 텍스트 저장 배열

	//////////버튼 텍스트 레이블//////////
	Label * label;

	//////////클릭 지연 타임//////////////
	float delay;

public:
	Button(const WCHAR * text, float px, float py);
	~Button();

	void init();
	void update();
	void draw();

	///////버튼 클릭 이벤트 메소드////////
	virtual void OnClick();
};
