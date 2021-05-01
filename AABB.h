#pragma once

class AABB  //AABB(Axis Aligned Bounding Box)
{
private:

	float ownerPx, ownerPy; //충돌체를 가지고 있는 게임오브젝트의..좌표

	float x, y;			 //사각형의 왼쪽상단 꼭지점 좌표
	float width, height; //사각형의 가로/세로 길이

	int id;              //충돌체 아이디

public:
	AABB(float x, float y, float width, float height, int id);
	virtual ~AABB();

	/////////충돌체를 가지고 있는 게임오브젝트의 좌표 지정//////
	void setOwnerPos(float px, float py);

	/////////AABB 출력하기-개발할때만...////////////
	void draw();

	/////////AABB의 꼭지점 가져오기 ////////////////
	void getBB(float &x0, float &y0, float &x1, float &y1);

	/////////AABB 아이디 가져오기///////////////////
	int getId();
};