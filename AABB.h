#pragma once

class AABB  //AABB(Axis Aligned Bounding Box)
{
private:

	float ownerPx, ownerPy; //�浹ü�� ������ �ִ� ���ӿ�����Ʈ��..��ǥ

	float x, y;			 //�簢���� ���ʻ�� ������ ��ǥ
	float width, height; //�簢���� ����/���� ����

	int id;              //�浹ü ���̵�

public:
	AABB(float x, float y, float width, float height, int id);
	virtual ~AABB();

	/////////�浹ü�� ������ �ִ� ���ӿ�����Ʈ�� ��ǥ ����//////
	void setOwnerPos(float px, float py);

	/////////AABB ����ϱ�-�����Ҷ���...////////////
	void draw();

	/////////AABB�� ������ �������� ////////////////
	void getBB(float &x0, float &y0, float &x1, float &y1);

	/////////AABB ���̵� ��������///////////////////
	int getId();
};