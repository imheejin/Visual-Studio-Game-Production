#include "stdafx.h"
#include "Sound.h"
#include "timer.h"
#include "GameObjectPool.h"

#pragma comment(lib, "fmod/lib/fmod_vc.lib")

FMOD_SYSTEM * Sound::system = NULL;

Sound::Sound() : GameObject("사운드", 2, true, 0,0)
{
	sound	= NULL;
	channel = NULL;

	lifeTime	= 0;
	useLifeTime = false;  //사운드 라이프 타임 적용안함

}

Sound::~Sound()
{
    ///////사운드 제거///////
	FMOD_Channel_Stop(channel);  //출력 중지
	FMOD_Sound_Release(sound);   //파일 언로드
}

void Sound::initSound()
{
	////////사운드 시스템 만들기//////////
	if (FMOD_System_Create(&system) != 0)
	{
		printf("Fmod 사운드 시스템 생성 실패\n");
	}

	////////사운드 시스템 초기화//////////
	if (FMOD_System_Init(system, 64, FMOD_INIT_NORMAL, NULL) != 0)
	{
		printf("Fmod 사운드 초기화 실패\n");
	}
}

void Sound::setLifeTime(float lifeTime)
{
	useLifeTime     = true;    //사운드 라이프 타임 사용
	this->lifeTime = lifeTime; //사운드 라이프 타임
}

void Sound::update()
{
	if (useLifeTime == true)
	{
		lifeTime = lifeTime - getDelteTime();

		if (lifeTime < 0)
		{
			////////////사운드를 자식으로 추가할 경우..오류발생함/////
			GameObjectPool::instance()->delGameObject(this);
		}
	}
}

void Sound::play(const char * fileName, bool loop)
{
	int mode = FMOD_LOOP_NORMAL;

	if (loop != true)  //한번재생으로...사운드 모드 변경
	{
		mode = FMOD_DEFAULT;
	}

	/////////파일을 로드해서..사운드 만들기////////
	if (FMOD_System_CreateSound(system, fileName, mode, NULL, &sound) != 0)
	{
		printf("사운드 파일 로드 실패 : %s\n", fileName);
	}
	
	////////사운드를..재생하는 채널 만들기////////
	if (FMOD_System_PlaySound(system, sound, NULL, false, &channel) != 0)
	{
		printf("사운드 플레이 실패\n");
	}
}

void Sound::exitSound()
{
	FMOD_System_Close(system);   //사운장치 끄기
	FMOD_System_Release(system); //사운장치 제거
}