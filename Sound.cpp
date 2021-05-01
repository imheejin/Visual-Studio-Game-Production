#include "stdafx.h"
#include "Sound.h"
#include "timer.h"
#include "GameObjectPool.h"

#pragma comment(lib, "fmod/lib/fmod_vc.lib")

FMOD_SYSTEM * Sound::system = NULL;

Sound::Sound() : GameObject("����", 2, true, 0,0)
{
	sound	= NULL;
	channel = NULL;

	lifeTime	= 0;
	useLifeTime = false;  //���� ������ Ÿ�� �������

}

Sound::~Sound()
{
    ///////���� ����///////
	FMOD_Channel_Stop(channel);  //��� ����
	FMOD_Sound_Release(sound);   //���� ��ε�
}

void Sound::initSound()
{
	////////���� �ý��� �����//////////
	if (FMOD_System_Create(&system) != 0)
	{
		printf("Fmod ���� �ý��� ���� ����\n");
	}

	////////���� �ý��� �ʱ�ȭ//////////
	if (FMOD_System_Init(system, 64, FMOD_INIT_NORMAL, NULL) != 0)
	{
		printf("Fmod ���� �ʱ�ȭ ����\n");
	}
}

void Sound::setLifeTime(float lifeTime)
{
	useLifeTime     = true;    //���� ������ Ÿ�� ���
	this->lifeTime = lifeTime; //���� ������ Ÿ��
}

void Sound::update()
{
	if (useLifeTime == true)
	{
		lifeTime = lifeTime - getDelteTime();

		if (lifeTime < 0)
		{
			////////////���带 �ڽ����� �߰��� ���..�����߻���/////
			GameObjectPool::instance()->delGameObject(this);
		}
	}
}

void Sound::play(const char * fileName, bool loop)
{
	int mode = FMOD_LOOP_NORMAL;

	if (loop != true)  //�ѹ��������...���� ��� ����
	{
		mode = FMOD_DEFAULT;
	}

	/////////������ �ε��ؼ�..���� �����////////
	if (FMOD_System_CreateSound(system, fileName, mode, NULL, &sound) != 0)
	{
		printf("���� ���� �ε� ���� : %s\n", fileName);
	}
	
	////////���带..����ϴ� ä�� �����////////
	if (FMOD_System_PlaySound(system, sound, NULL, false, &channel) != 0)
	{
		printf("���� �÷��� ����\n");
	}
}

void Sound::exitSound()
{
	FMOD_System_Close(system);   //�����ġ ����
	FMOD_System_Release(system); //�����ġ ����
}