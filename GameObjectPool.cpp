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
	objs[order].push_back(o);  //게임오브젝트 추가
	o->init();          //게임 오브젝트 초기화 
}

void GameObjectPool::delGameObject(GameObject *o)
{
	o->setAlive(false);  //게임오브젝트가 죽었음 - 제거해야함

	////////////객체가 지워지면...지워진객체로 만든 충돌쌍을 모두 제거해야함//////////
	for (int i = 0; i < cols.size(); )
	{
		GameObject *A = cols[i]->GetGameObjectA();
		GameObject *B = cols[i]->GetGameObjectB();

		if (o == A || o == B)
		{			
			/////////////충돌이 끝났음을 알려줌//////////
			AABB * aa = cols[i]->GetAABBaa();  //A 오브젝트의..충돌체
			AABB * ab = cols[i]->GetAABBab();  //B 오브젝트의..충돌체

			A->OnCollisionExit(B, ab, aa);  //A 객체에..충돌끝남을 아림
			B->OnCollisionExit(A, aa, ab);  //B 객체에..충돌끝남을 알림
			
			//[1]충돌체 delete 하기
			delete cols[i];

			//[2]stl vector의 공간 삭제하기
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
			GameObject * o = objs[l][i];  //l 레이어에서..i 번째 게임오브젝트를 가져옴

			if (o->getAlive() == false)   //죽은 게임오브젝트임
			{
				
				delete o;  //객체 제거하기

				objs[l].erase(objs[l].begin() + i);  //stl vector에서 i 번째 객체저장 자리 제거

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
	//////////////기존의 모든 충돌쌍이 충돌하지 않았음으로 표시/////////
	resetColPair();

	//////////같은 레이어 간의 충돌 검사/////////
	for (int l = 0; l < MAX_LAYERS; l++)
	{
		checkColSameLayer(l);
	}

	///////////다른 레이어 간의 충돌 검사/////////
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

	///////////////충돌검사 완료시에...다시 충돌되지 않은 쌍은 ... 충돌쌍에 제거함////////
	popColPair();
}

GameObject * GameObjectPool::find(const char * name)
{
	for (int l = 0; l < MAX_LAYERS; l++)
	{
		for (int i = 0; i < objs[l].size(); i++)
		{
			GameObject * o = objs[l][i];

			////////이름 검사(비교)하기////////
			if (strcmp(o->getName(), name) == 0)
			{
				return o;  //해당 이름의..게임오브젝트를 반환함
			}
		}
	}

	return NULL;  //해당 이름의..게임 오브젝트가 없음
}

void GameObjectPool::checkColDiffLayer(int layer1, int layer2)  //다른 레이어에 있는 오브젝트 충돌검사
{
	for (int j = 0; j < objs[layer1].size(); j++) //layer1 번째 레이어 반복
	{ 
		for (int i = 0; i < objs[layer2].size(); i++) //layer2 번째 레이어 반복
		{

				//////////충돌체 가져오기//////////
				std::vector<AABB *> * colI = objs[layer2][i]->getCols();
				std::vector<AABB *> * colJ = objs[layer1][j]->getCols();

				for (int jj = 0; jj < colJ->size(); jj++)
				{
					for (int ii = 0; ii < colI->size(); ii++)
					{
						//////////AABB 꼭지점 가져오기//////
						float x0, y0, x1, y1;
						float a0, b0, a1, b1;

						(*colI)[ii]->getBB(x0, y0, x1, y1);
						(*colJ)[jj]->getBB(a0, b0, a1, b1);

						if (b0 <= y1 && b1 >= y0 && a1 >= x0 && a0 <= x1)
						{
							GameObject * objI = objs[layer2][i];
							GameObject * objJ = objs[layer1][j];

							////i 번째..오브젝트에..j 번재와 충돌함을 알림
							objI->OnCollision(objJ, (*colJ)[jj], (*colI)[ii]);

							////j 번째 ...오브젝트에..i 번재와 충돌함을 알림
							objJ->OnCollision(objI, (*colI)[ii], (*colJ)[jj]);

							/////////////////////충돌쌍 저장하기//////////////
							pushColPair(objI, (*colI)[ii], objJ, (*colJ)[jj]);
						}
					}
				}
			}
		}
}


void GameObjectPool::checkColSameLayer(int layer)  //같은 레이어에 있는 오브젝트 충돌검사
{
	//////////////충돌 검사하기////////////
	for (int j = 0; j < objs[layer].size(); j++)
	{
		for (int i = 0; i < objs[layer].size(); i++)
		{
			if (i > j)
			{
				////printf("%s \n", objs[2][j]->getName());

				//////////충돌체 가져오기//////////
				std::vector<AABB *> * colI = objs[layer][i]->getCols();
				std::vector<AABB *> * colJ = objs[layer][j]->getCols();

				for (int jj = 0; jj < colJ->size(); jj++)
				{
					for (int ii = 0; ii < colI->size(); ii++)
					{
						//////////AABB 꼭지점 가져오기//////
						float x0, y0, x1, y1;
						float a0, b0, a1, b1;

						(*colI)[ii]->getBB(x0, y0, x1, y1);
						(*colJ)[jj]->getBB(a0, b0, a1, b1);

						if (b0 <= y1 && b1 >= y0 && a1 >= x0 && a0 <= x1)
						{
							GameObject * objI = objs[layer][i];
							GameObject * objJ = objs[layer][j];

							////i 번째..오브젝트에..j 번재와 충돌함을 알림
							objI->OnCollision(objJ, (*colJ)[jj], (*colI)[ii]);

							////j 번째 ...오브젝트에..i 번재와 충돌함을 알림
							objJ->OnCollision(objI, (*colI)[ii], (*colJ)[jj]);

							/////////////////////충돌쌍 저장하기//////////////
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
		////////i 번째 충돌쌍이 ... (A, aa, B, bb와 같은 충돌쌍인지를 검사함)
		if (cols[i]->isEqual(A, aa, B, ab) == true)
		{ 
			///////////지원진 객체...상태변경하지 않기////////
			if (A->getAlive() == true && B->getAlive() == true)
			{
				cols[i]->SetState(ColPair::Col);  //기존 충돌쌍이 다시..충돌했음으로..상태를 변경함
			}
			
			return;
		}
	}

	/////////////충돌정보를 객체에 전달하기//////////////
	A->OnCollisionEnter(B, ab, aa);  //A객체에게 B와 충돌이 시작되었음을 알림
	B->OnCollisionEnter(A, aa, ab);  //B객체에게 A와 충돌이 시작되었음을 알림

	////////////지워진 객체를 충돌쌍으로..저장하지 않음//////////

	if (A->getAlive() == true && B->getAlive() == true)
	{
		////////////기존에 충돌한 충돌체가 없음 - 충돌체 추가////////////
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
		if (cols[i]->GetState() == ColPair::NotCol) //충돌검사중에..충돌이 안됨
		{
			GameObject *A = cols[i]->GetGameObjectA();
			AABB       *aa= cols[i]->GetAABBaa();

			GameObject *B  = cols[i]->GetGameObjectB();
			AABB       *ab = cols[i]->GetAABBab();

			/////////충돌쌍 delete하기////////
			delete cols[i];

			//////////충돌쌍 제거하기/////////
			cols.erase(cols.begin() + i);

			/////////////충돌정보를 객체에 전달하기//////////////
			A->OnCollisionExit(B, ab, aa);  //A객체에게 B와 충돌이 끝났음을  알림
			B->OnCollisionExit(A, aa, ab);  //B객체에게 A와 충돌이 끝났음을  알림

			//printf("%s[%d] 와 %s[%d] 가 충돌이 끝남\n", A->getName(), aa->getId(), B->getName(), ab->getId());
		}
	}
	
	//printf("----------------------------------\n");
}

void GameObjectPool::clear()
{
	////////레이어에 저장된 게임 객체 제거하기//////////
	for (int l = 0; l < MAX_LAYERS; l++)
	{
		for (int i = 0; i < objs[l].size(); i++)
		{
			delete objs[l][i];
		}
			objs[l].clear();
	}

	////////////////모든 충돌쌍 삭제하기////////////////
	for (int i = 0; i < cols.size(); i++)
	{
		delete cols[i];
	}
		cols.clear();
}