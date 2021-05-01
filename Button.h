#pragma once

#include <Windows.h>
#include "SpriteObject.h"
#include "Label.h"

class Button : public SpriteObject
{
protected:

	enum State{normal, pressed, click};

	State state;    //��ư ���� ���� ����
	WCHAR text[16]; //��ư �ؽ�Ʈ ���� �迭

	//////////��ư �ؽ�Ʈ ���̺�//////////
	Label * label;

	//////////Ŭ�� ���� Ÿ��//////////////
	float delay;

public:
	Button(const WCHAR * text, float px, float py);
	~Button();

	void init();
	void update();
	void draw();

	///////��ư Ŭ�� �̺�Ʈ �޼ҵ�////////
	virtual void OnClick();
};
