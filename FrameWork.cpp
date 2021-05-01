#include "stdafx.h"
#include "FrameWork.h"
#include "graphic.h"
#include "input.h"
#include "timer.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "Sound.h"

FrameWork * FrameWork::framework = NULL;

////////������, �Ҹ���/////////
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

void FrameWork::init(HWND hWnd, int width, int height)  //�ʱ�ȭ 
{
	////////////�׷���, Ÿ�̸�, �Է� �ʱ�ȭ �ϱ�////////////////
	initGraphic(hWnd, 0, 0, width, height);
	initInput();
	initTimer();

	Sound::initSound();

	////////////���� �� ��ü..�����ϱ�/////////////
	scene = new TitleScene();
	//scene = new GameScene();
	scene->init();

	////////////���� �̵����� NULL �� �ʱ�ȭ////////
	this->nextScene = NULL;  //NULL�� ���������� �̵����� ����

	/////////////������ �ڵ� �����ϱ�/////////////
	this->hWnd = hWnd;
}

void FrameWork::run()   //���� ���۽�Ű��-���ӽ���
{
	clear(0, 0, 0);
	updateInput();
	updateTimer();

	////////�� ������Ʈ - ���ӿ�����Ʈ ������Ʈ//////
	scene->update();

	////////�� �浹�˻� - ���ӿ�����Ʈ �浹�˻�//////
	scene->checkCol();

	//////// ������Ʈ �Ǵ� �浹����..����..���� ���ӿ�����Ʈ �����ϱ�//////
	scene->removeDeadObj();

	////////�� Draw - ���ӿ�����Ʈ ���(draw)///////
	scene->draw();

	////////������ ��ȯ ���//////
	if (nextScene != NULL)
	{
		///////���� �� �����ϱ�////
		scene->exit();
		delete scene;

		///////������ �ε��ϱ�/////
		scene = nextScene;
		scene->init();

		///////�� ��ȯ�Ϸ�////////
		nextScene = NULL;
	}

	render();
}

void FrameWork::LoadScene(Scene * nextScene)
{
	this->nextScene = nextScene;

	////////���� �� �����ϱ�///////
	/*******************************
	scene->exit();  //Scene Unload
	delete scene;

	////////���ο� ������..��ü�ϱ�////
	scene = nextScene; //���ο� �� ..������ ����
	scene->init();     //Scene Load (�ʱ�ȭ)
	********************************/
}


void FrameWork::exit()  //����ó��
{
	///////�� �����ϱ�///////////
	scene->exit();
	delete scene;

	///////���� ó���ϱ�////////
	exitGraphic();
	exitInput();
	exitTimer();

	Sound::exitSound();
}

void FrameWork::ApplicationQuit()
{
	////////������ ���α׷� ����//////
	DestroyWindow(hWnd);
}