#pragma once

#include "GameObject.h"

class TestObj : public GameObject
{
private:

public:
	TestObj(float px, float py);
	~TestObj();

	void init();
};