#pragma once

#include "GameObject.h"
#include "fmod/inc/fmod.h"

class Sound : public GameObject
{
private:

	///////사운드 시스템 스태틱 포인터/////
	static FMOD_SYSTEM * system;

	////////사운드, 사운드 채널////////
	FMOD_SOUND   * sound;
	FMOD_CHANNEL * channel;

	////////타임아웃-라이프타임 변수/////
	float lifeTime;
	bool  useLifeTime;

public:
	Sound();
	~Sound();

	static void initSound();
	static void exitSound();

	void setLifeTime(float lifeTime);
	void update();

	void play(const char * fileName, bool loop);
};
