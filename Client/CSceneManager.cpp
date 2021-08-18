#include "pch.h"

#include "CSceneManager.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"


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
	m_arrScene[TYPE_NUMBER(SCENE_TYPE::START)] = new CScene_Start;
	m_arrScene[TYPE_NUMBER(SCENE_TYPE::START)]->SetSceneName(L"Start Scene");

	m_arrScene[TYPE_NUMBER(SCENE_TYPE::TOOL)] = new CScene_Tool;
	m_arrScene[TYPE_NUMBER(SCENE_TYPE::TOOL)]->SetSceneName(L"Tool Scene");

	m_currentScene = m_arrScene[TYPE_NUMBER(SCENE_TYPE::TOOL)];
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
	m_currentScene->Exit();
	m_currentScene = m_arrScene[TYPE_NUMBER(_next)];
	m_currentScene->Enter();
}
