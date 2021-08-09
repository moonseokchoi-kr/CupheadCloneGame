#pragma once
/// <summary>
/// ���ӿ�����Ʈ�� �����Ǵ� ����� ���������� �����ϴ� ���Ŵ��� Ŭ����
/// </summary>
/// 
/// �ۼ��� : �ֹ���
/// �ۼ��� : 2021-06-30
/// ���� : 1.0
/// ���� ���� : �⺻���� �������� ������Ʈ���� �ۼ�
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

