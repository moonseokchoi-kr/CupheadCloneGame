#include "pch.h"

#include "CSceneManager.h"
#include "CScene_Test.h"
#include "CScene_Tool.h"
#include "CUIManager.h"
#include "CColliderManager.h"
#include "CStageScene_01.h"
#include "CStageScene_02.h"
#include "CStartScene.h"
CSceneManager::CSceneManager()
	:m_arrScene{}
	,m_currentScene(nullptr)
{

}

CSceneManager::~CSceneManager()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}
void CSceneManager::Init()
{
	m_arrScene[TYPE_NUMBER(SCENE_TYPE::TEST)] = new CScene_Test;
	m_arrScene[TYPE_NUMBER(SCENE_TYPE::TEST)]->SetSceneName(L"Test Scene");

	m_arrScene[TYPE_NUMBER(SCENE_TYPE::START)] = new CStartScene;
	m_arrScene[TYPE_NUMBER(SCENE_TYPE::START)]->SetSceneName(L"Start Scene");

	m_arrScene[TYPE_NUMBER(SCENE_TYPE::TOOL)] = new CScene_Tool;
	m_arrScene[TYPE_NUMBER(SCENE_TYPE::TOOL)]->SetSceneName(L"Tool Scene");

	m_arrScene[TYPE_NUMBER(SCENE_TYPE::STAGE_01)] = new CStageScene_01;
	m_arrScene[TYPE_NUMBER(SCENE_TYPE::STAGE_01)]->SetSceneName(L"STAGE01 Scene");

	m_arrScene[TYPE_NUMBER(SCENE_TYPE::STAGE_02)] = new CStageScene_02;
	m_arrScene[TYPE_NUMBER(SCENE_TYPE::STAGE_02)]->SetSceneName(L"STAGE02 Scene");


	m_currentScene = m_arrScene[TYPE_NUMBER(SCENE_TYPE::START)];
	m_currentScene->Enter();
}

void CSceneManager::Update()
{
	m_currentScene->Update();
	m_currentScene->FinalUpdate();
}


void CSceneManager::Render(HDC _dc)
{
	m_currentScene->Render(_dc);
}

void CSceneManager::ChangeScene(SCENE_TYPE _next)
{
	CUIManager::GetInst()->SetFocusedUI(nullptr);
	CColliderManager::GetInst()->Reset();
	m_currentScene->Exit();
	m_currentScene = m_arrScene[TYPE_NUMBER(_next)];
	m_currentScene->Enter();
}
