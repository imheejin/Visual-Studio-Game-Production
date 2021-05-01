#pragma once

#include "Scene.h"

class FrameWork
{
private:

	////////������, �Ҹ���/////////
	FrameWork();
	virtual ~FrameWork();

	////////��ü(�ν��Ͻ�) ������ ���� ����ƽ ����///////
	static FrameWork * framework;

	////////���� ������� �� ��ü..���� ������///////////
	Scene * scene, *nextScene;

	////////������ �ڵ� ���� /////////
	HWND hWnd;
	
public:

	static FrameWork * instance();

	////////������ ��ũ Ȱ�� �޼ҵ�/////////
	void init(HWND hWnd, int width, int height);  //�ʱ�ȭ 
	void run();   //���� ���۽�Ű��-���ӽ���
	void exit();  //����ó��

	///////////////���ε��ϱ�///////////////
	void LoadScene(Scene * nextScene);

	///////////////���� ���� ���////////////
	void ApplicationQuit();
};