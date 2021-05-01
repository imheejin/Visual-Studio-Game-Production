#pragma once

class Scene
{
private:
public:
	Scene();
	virtual ~Scene();

	///////씬 활용 함수(메소드)////////
	virtual void init();          //스테이지 로드 및 초기화
	virtual void update();        //게임 오브젝트 업데이트
	virtual void checkCol();      //게임 오브젝트 충돌검사하기
	virtual void removeDeadObj(); //죽은 게임오브젝트 삭제하기 
	virtual void draw();          //게임 오브젝트 출력하기
	virtual void exit();          //스테이지 제거
};