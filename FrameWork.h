#pragma once

#include "Scene.h"

class FrameWork
{
private:

	////////생성자, 소멸자/////////
	FrameWork();
	virtual ~FrameWork();

	////////객체(인스턴스) 포인터 저장 스태틱 변수///////
	static FrameWork * framework;

	////////현재 사용중인 씬 객체..저장 포인터///////////
	Scene * scene, *nextScene;

	////////윈도우 핸들 저장 /////////
	HWND hWnd;
	
public:

	static FrameWork * instance();

	////////프레임 워크 활용 메소드/////////
	void init(HWND hWnd, int width, int height);  //초기화 
	void run();   //씬을 동작시키기-게임실행
	void exit();  //종료처리

	///////////////씬로드하기///////////////
	void LoadScene(Scene * nextScene);

	///////////////게임 종료 기능////////////
	void ApplicationQuit();
};