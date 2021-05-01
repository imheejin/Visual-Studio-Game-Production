#include "stdafx.h"
#include "GameObjectPool.h"

GameObjectPool * GameObjectPool::pool = NULL;

GameObjectPool::GameObjectPool()
{
}

GameObjectPool::~GameObjectPool()
{
}

GameObjectPool * GameObjectPool::instance()
{
	if (GameObjectPool::pool == NULL) //pool
	{
		pool=new GameObjectPool();
	}
	return pool;
}

void GameObjectPool::addGameObject(GameObject * o, int order)
{
	objs[order].push_back(o);  //���ӿ�����Ʈ �߰�
	o->init();          //���� ������Ʈ �ʱ�ȭ 
}

void GameObjectPool::delGameObject(GameObject *o)
{
	o->setAlive(false);  //���ӿ�����Ʈ�� �׾��� - �����ؾ���

	////////////��ü�� ��������...��������ü�� ���� �浹���� ��� �����ؾ���//////////
	for (int i = 0; i < cols.size(); )
	{
		GameObject *A = cols[i]->GetGameObjectA();
		GameObject *B = cols[i]->GetGameObjectB();

		if (o == A || o == B)
		{			
			/////////////�浹�� �������� �˷���//////////
			AABB * aa = cols[i]->GetAABBaa();  //A ������Ʈ��..�浹ü
			AABB * ab = cols[i]->GetAABBab();  //B ������Ʈ��..�浹ü

			A->OnCollisionExit(B, ab, aa);  //A ��ü��..�浹������ �Ƹ�
			B->OnCollisionExit(A, aa, ab);  //B ��ü��..�浹������ �˸�
			
			//[1]�浹ü delete �ϱ�
			delete cols[i];

			//[2]stl vector�� ���� �����ϱ�
			cols.erase(cols.begin() + i);
		}
		else {
			i++;
		}
	}
}

void GameObjectPool::removeDeadObj()
{
	for (int l = 0; l < MAX_LAYERS; l++)
	{
		for (int i = 0; i < objs[l].size(); i++)
		{
			GameObject * o = objs[l][i];  //l ���̾��..i ��° ���ӿ�����Ʈ�� ������

			if (o->getAlive() == false)   //���� ���ӿ�����Ʈ��
			{
				
				delete o;  //��ü �����ϱ�

				objs[l].erase(objs[l].begin() + i);  //stl vector���� i ��° ��ü���� �ڸ� ����

			}
		}
	}
}

void GameObjectPool::update()
{
	for (int l = 0; l < MAX_LAYERS; l++)
	{
		for (int i = 0; i < objs[l].size(); i++)
		{
			objs[l][i]->update();
		}
	}
}

void GameObjectPool::draw()
{
	for (int l = 0; l < MAX_LAYERS; l++)
	{
		for (int i = 0; i < objs[l].size(); i++)
		{
			if (objs[l][i]->getState() == true)
			{
				objs[l][i]->draw();
			}
		}
	}
}

void GameObjectPool::checkCol()
{
	//////////////������ ��� �浹���� �浹���� �ʾ������� ǥ��/////////
	resetColPair();

	//////////���� ���̾� ���� �浹 �˻�/////////
	for (int l = 0; l < MAX_LAYERS; l++)
	{
		checkColSameLayer(l);
	}

	///////////�ٸ� ���̾� ���� �浹 �˻�/////////
	for (int j = 0; j < MAX_LAYERS; j++)
	{
		for (int i = 0; i < MAX_LAYERS; i++)
		{
			if (i > j)
			{
				checkColDiffLayer(i, j);
			}
		}
	}

	///////////////�浹�˻� �Ϸ�ÿ�...�ٽ� �浹���� ���� ���� ... �浹�ֿ� ������////////
	popColPair();
}

GameObject * GameObjectPool::find(const char * name)
{
	for (int l = 0; l < MAX_LAYERS; l++)
	{
		for (int i = 0; i < objs[l].size(); i++)
		{
			GameObject * o = objs[l][i];

			////////�̸� �˻�(��)�ϱ�////////
			if (strcmp(o->getName(), name) == 0)
			{
				return o;  //�ش� �̸���..���ӿ�����Ʈ�� ��ȯ��
			}
		}
	}

	return NULL;  //�ش� �̸���..���� ������Ʈ�� ����
}

void GameObjectPool::checkColDiffLayer(int layer1, int layer2)  //�ٸ� ���̾ �ִ� ������Ʈ �浹�˻�
{
	for (int j = 0; j < objs[layer1].size(); j++) //layer1 ��° ���̾� �ݺ�
	{ 
		for (int i = 0; i < objs[layer2].size(); i++) //layer2 ��° ���̾� �ݺ�
		{

				//////////�浹ü ��������//////////
				std::vector<AABB *> * colI = objs[layer2][i]->getCols();
				std::vector<AABB *> * colJ = objs[layer1][j]->getCols();

				for (int jj = 0; jj < colJ->size(); jj++)
				{
					for (int ii = 0; ii < colI->size(); ii++)
					{
						//////////AABB ������ ��������//////
						float x0, y0, x1, y1;
						float a0, b0, a1, b1;

						(*colI)[ii]->getBB(x0, y0, x1, y1);
						(*colJ)[jj]->getBB(a0, b0, a1, b1);

						if (b0 <= y1 && b1 >= y0 && a1 >= x0 && a0 <= x1)
						{
							GameObject * objI = objs[layer2][i];
							GameObject * objJ = objs[layer1][j];

							////i ��°..������Ʈ��..j ����� �浹���� �˸�
							objI->OnCollision(objJ, (*colJ)[jj], (*colI)[ii]);

							////j ��° ...������Ʈ��..i ����� �浹���� �˸�
							objJ->OnCollision(objI, (*colI)[ii], (*colJ)[jj]);

							/////////////////////�浹�� �����ϱ�//////////////
							pushColPair(objI, (*colI)[ii], objJ, (*colJ)[jj]);
						}
					}
				}
			}
		}
}


void GameObjectPool::checkColSameLayer(int layer)  //���� ���̾ �ִ� ������Ʈ �浹�˻�
{
	//////////////�浹 �˻��ϱ�////////////
	for (int j = 0; j < objs[layer].size(); j++)
	{
		for (int i = 0; i < objs[layer].size(); i++)
		{
			if (i > j)
			{
				////printf("%s \n", objs[2][j]->getName());

				//////////�浹ü ��������//////////
				std::vector<AABB *> * colI = objs[layer][i]->getCols();
				std::vector<AABB *> * colJ = objs[layer][j]->getCols();

				for (int jj = 0; jj < colJ->size(); jj++)
				{
					for (int ii = 0; ii < colI->size(); ii++)
					{
						//////////AABB ������ ��������//////
						float x0, y0, x1, y1;
						float a0, b0, a1, b1;

						(*colI)[ii]->getBB(x0, y0, x1, y1);
						(*colJ)[jj]->getBB(a0, b0, a1, b1);

						if (b0 <= y1 && b1 >= y0 && a1 >= x0 && a0 <= x1)
						{
							GameObject * objI = objs[layer][i];
							GameObject * objJ = objs[layer][j];

							////i ��°..������Ʈ��..j ����� �浹���� �˸�
							objI->OnCollision(objJ, (*colJ)[jj], (*colI)[ii]);

							////j ��° ...������Ʈ��..i ����� �浹���� �˸�
							objJ->OnCollision(objI, (*colI)[ii], (*colJ)[jj]);

							/////////////////////�浹�� �����ϱ�//////////////
							pushColPair(objI, (*colI)[ii], objJ, (*colJ)[jj]);
						}
					}
				}
			}
		}
	}
}

void GameObjectPool::pushColPair(GameObject * A, AABB * aa, GameObject * B, AABB *ab)
{
	for (int i = 0; i < cols.size(); i++)
	{
		////////i ��° �浹���� ... (A, aa, B, bb�� ���� �浹�������� �˻���)
		if (cols[i]->isEqual(A, aa, B, ab) == true)
		{ 
			///////////������ ��ü...���º������� �ʱ�////////
			if (A->getAlive() == true && B->getAlive() == true)
			{
				cols[i]->SetState(ColPair::Col);  //���� �浹���� �ٽ�..�浹��������..���¸� ������
			}
			
			return;
		}
	}

	/////////////�浹������ ��ü�� �����ϱ�//////////////
	A->OnCollisionEnter(B, ab, aa);  //A��ü���� B�� �浹�� ���۵Ǿ����� �˸�
	B->OnCollisionEnter(A, aa, ab);  //B��ü���� A�� �浹�� ���۵Ǿ����� �˸�

	////////////������ ��ü�� �浹������..�������� ����//////////

	if (A->getAlive() == true && B->getAlive() == true)
	{
		////////////������ �浹�� �浹ü�� ���� - �浹ü �߰�////////////
		cols.push_back(new ColPair(A, aa, B, ab));
	}
	
}

void GameObjectPool::resetColPair()
{
	for (int i = 0; i < cols.size(); i++)
	{
		cols[i]->SetState(ColPair::NotCol);
	}
}

void GameObjectPool::popColPair()
{
	for (int i = 0; i < cols.size(); i++)
	{
		if (cols[i]->GetState() == ColPair::NotCol) //�浹�˻��߿�..�浹�� �ȵ�
		{
			GameObject *A = cols[i]->GetGameObjectA();
			AABB       *aa= cols[i]->GetAABBaa();

			GameObject *B  = cols[i]->GetGameObjectB();
			AABB       *ab = cols[i]->GetAABBab();

			/////////�浹�� delete�ϱ�////////
			delete cols[i];

			//////////�浹�� �����ϱ�/////////
			cols.erase(cols.begin() + i);

			/////////////�浹������ ��ü�� �����ϱ�//////////////
			A->OnCollisionExit(B, ab, aa);  //A��ü���� B�� �浹�� ��������  �˸�
			B->OnCollisionExit(A, aa, ab);  //B��ü���� A�� �浹�� ��������  �˸�

			//printf("%s[%d] �� %s[%d] �� �浹�� ����\n", A->getName(), aa->getId(), B->getName(), ab->getId());
		}
	}
	
	//printf("----------------------------------\n");
}

void GameObjectPool::clear()
{
	////////���̾ ����� ���� ��ü �����ϱ�//////////
	for (int l = 0; l < MAX_LAYERS; l++)
	{
		for (int i = 0; i < objs[l].size(); i++)
		{
			delete objs[l][i];
		}
			objs[l].clear();
	}

	////////////////��� �浹�� �����ϱ�////////////////
	for (int i = 0; i < cols.size(); i++)
	{
		delete cols[i];
	}
		cols.clear();
}