#pragma once

class Scene
{
private:
public:
	Scene();
	virtual ~Scene();

	///////�� Ȱ�� �Լ�(�޼ҵ�)////////
	virtual void init();          //�������� �ε� �� �ʱ�ȭ
	virtual void update();        //���� ������Ʈ ������Ʈ
	virtual void checkCol();      //���� ������Ʈ �浹�˻��ϱ�
	virtual void removeDeadObj(); //���� ���ӿ�����Ʈ �����ϱ� 
	virtual void draw();          //���� ������Ʈ ����ϱ�
	virtual void exit();          //�������� ����
};