#include "stdafx.h"
#include "TestObj.h"

TestObj::TestObj(float px, float py) : GameObject("Å×½ºÆ®", 1, true, px, py)
{}

TestObj::~TestObj()
{
}

void TestObj::init()
{
	addCollider(new AABB(0, 0, 70, 70, 0));
}
