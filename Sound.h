#pragma once

#include "GameObject.h"
#include "fmod/inc/fmod.h"

class Sound : public GameObject
{
private:

	///////���� �ý��� ����ƽ ������/////
	static FMOD_SYSTEM * system;

	////////����, ���� ä��////////
	FMOD_SOUND   * sound;
	FMOD_CHANNEL * channel;

	////////Ÿ�Ӿƿ�-������Ÿ�� ����/////
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
