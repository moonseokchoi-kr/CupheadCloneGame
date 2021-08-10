#include "pch.h"
#include "CBackGroundManager.h"
#include "CBackGround.h"
#include "CScene.h"
#include "CTexture.h"


#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CResourceManager.h"
#include "CUIManager.h"

CBackGroundManager::CBackGroundManager()
	:m_focusedBack(nullptr)
	,m_prevTargetBack(nullptr)
{

}

CBackGroundManager::~CBackGroundManager()
{

}

void CBackGroundManager::Update()
{
	CScene* curScene = CSceneManager::GetInst()->GetCurrentScene();
	
	if (curScene->GetSceneName() != L"Tool Scene")
	{
		return;
	}
	if (CUIManager::GetInst()->GetFocusedUI() != nullptr)
	{
		return;
	}

	m_focusedBack = getFocusedObj();
	bool lButtonTap = KEY_TAP(KEY::MOUSE_LBUTTON);
	bool lButtonAway = KEY_AWAY(KEY::MOUSE_LBUTTON);
	if (nullptr != m_focusedBack)
	{
		m_focusedBack->MouseOn();

		if (lButtonTap)
		{
			m_focusedBack->MouseLButtonDown();
			m_focusedBack->m_lbuttonDown = true;
		}
		if (lButtonAway)
		{
			m_focusedBack->MouseLButtonUp();
			if (m_focusedBack->IsLButtonDown())
			{

			}
			m_focusedBack->m_lbuttonDown = false;

		}
	}
}

CBackGround* CBackGroundManager::getFocusedObj()
{
	CScene* curScene = CSceneManager::GetInst()->GetCurrentScene();
	const vector<CObject*>& backgrounds = curScene->GetObjWithType(GROUP_TYPE::BACK_GROUND);

	vector<CObject*>::const_iterator iter = backgrounds.begin();
	vector<CObject*>::const_iterator targetIter = backgrounds.end();

	CBackGround* focusBackObj = m_focusedBack;
	bool lButtonTap = KEY_TAP(KEY::MOUSE_LBUTTON);

	//현재 포커스 유지
	if (!lButtonTap)
	{
		return m_focusedBack;
	}

	for (; iter != backgrounds.end(); ++iter)
	{
		if (((CBackGround*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	if (backgrounds.end() == targetIter)
	{
		return nullptr;
	}

	focusBackObj = (CBackGround*)*targetIter;
	curScene->ChangeFocus(targetIter, focusBackObj, GROUP_TYPE::BACK_GROUND);

	return focusBackObj;
}
