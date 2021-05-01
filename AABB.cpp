#include "stdafx.h"
#include "AABB.h"
#include "graphic.h"

AABB::AABB(float x, float y, float width, float height, int id)
{
	this->x = x;
	this->y = y;
	this->width  = width;
	this->height = height;

	this->id = id;

	this->ownerPx = 0;
	this->ownerPy = 0;
}

AABB::~AABB()
{
}

void AABB::draw()
{
	int x0 = ownerPx + x;
	int y0 = ownerPy + y;
	int x1 = x0 + width;
	int y1 = y0 + height;

	drawRect(x0, y0, x1, y1, 255, 0, 0);
}

void AABB::setOwnerPos(float px, float py)
{
	ownerPx = px;
	ownerPy = py;
}

void AABB::getBB(float &x0, float &y0, float &x1, float &y1)
{
	x0 = ownerPx + x;
	y0 = ownerPy + y;
	x1 = x0 + width;
	y1 = y0 + height;
}

int AABB::getId()
{
	return id;
}