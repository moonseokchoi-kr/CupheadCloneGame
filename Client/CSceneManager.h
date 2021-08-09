#pragma once
/// <summary>
/// 게임오브젝트가 관리되는 장면을 종합적으로 관리하는 장면매니저 클래스
/// </summary>
/// 
/// 작성자 : 최문석
/// 작성일 : 2021-06-30
/// 버전 : 1.0
/// 버전 내용 : 기본적인 렌더링및 업데이트구조 작성
/// 
#include "CScene.h"
class CSceneManager
{
	SINGLE(CSceneManager);
public:
	void Init();
	void Update();
	void Render(HDC _dc);
	
public:
	array<CScene*,(UINT)SCENE_TYPE::END>& GetSceneArray() { return m_arrScene; }
	CScene* GetCurrentScene() { return m_currentScene; }
private:
	void ChangeScene(SCENE_TYPE _next);
private:
	array<CScene*, (UINT)SCENE_TYPE::END> m_arrScene;
	CScene* m_currentScene;

friend class CEventManager;
};

