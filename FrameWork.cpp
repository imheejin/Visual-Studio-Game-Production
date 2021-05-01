#include "stdafx.h"
#include "FrameWork.h"
#include "graphic.h"
#include "input.h"
#include "timer.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "Sound.h"

FrameWork * FrameWork::framework = NULL;

////////생성자, 소멸자/////////
FrameWork::FrameWork()
{
}

FrameWork::~FrameWork()
{
}

FrameWork * FrameWork::instance()
{
	if (framework == NULL)
	{
		framework = new FrameWork();
	}

	return framework;
}

void FrameWork::init(HWND hWnd, int width, int height)  //초기화 
{
	////////////그래픽, 타이머, 입력 초기화 하기////////////////
	initGraphic(hWnd, 0, 0, width, height);
	initInput();
	initTimer();

	Sound::initSound();

	////////////시작 씬 객체..생성하기/////////////
	scene = new TitleScene();
	//scene = new GameScene();
	scene->init();

	////////////다음 이동씬은 NULL 로 초기화////////
	this->nextScene = NULL;  //NULL은 다음씬으로 이동하지 않음

	/////////////윈도우 핸들 저장하기/////////////
	this->hWnd = hWnd;
}

void FrameWork::run()   //씬을 동작시키기-게임실행
{
	clear(0, 0, 0);
	updateInput();
	updateTimer();

	////////씬 업데이트 - 게임오브젝트 업데이트//////
	scene->update();

	////////씬 충돌검사 - 게임오브젝트 충돌검사//////
	scene->checkCol();

	//////// 업데이트 또는 충돌에서..에서..죽은 게임오브젝트 제거하기//////
	scene->removeDeadObj();

	////////씬 Draw - 게임오브젝트 출력(draw)///////
	scene->draw();

	////////다음씬 전환 기능//////
	if (nextScene != NULL)
	{
		///////현재 씬 제거하기////
		scene->exit();
		delete scene;

		///////다음씬 로드하기/////
		scene = nextScene;
		scene->init();

		///////씬 전환완료////////
		nextScene = NULL;
	}

	render();
}

void FrameWork::LoadScene(Scene * nextScene)
{
	this->nextScene = nextScene;

	////////기존 씬 제거하기///////
	/*******************************
	scene->exit();  //Scene Unload
	delete scene;

	////////새로운 씬으로..교체하기////
	scene = nextScene; //새로운 씬 ..포인터 저장
	scene->init();     //Scene Load (초기화)
	********************************/
}


void FrameWork::exit()  //종료처리
{
	///////씬 종료하기///////////
	scene->exit();
	delete scene;

	///////종료 처리하기////////
	exitGraphic();
	exitInput();
	exitTimer();

	Sound::exitSound();
}

void FrameWork::ApplicationQuit()
{
	////////윈도우 프로그램 종료//////
	DestroyWindow(hWnd);
}