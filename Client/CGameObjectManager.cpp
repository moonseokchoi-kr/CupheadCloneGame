#include "pch.h"
#include "CGameObjectManager.h"
#include "CBackGround.h"

#include "CScene.h"
#include "CTexture.h"


#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CResourceManager.h"
#include "CUIManager.h"

CGameObjectManager::CGameObjectManager()
	:m_focusObj(nullptr)
	,m_prevTargetObj(nullptr)
	,m_currentType(GROUP_TYPE::BACK_GROUND)
{

}

CGameObjectManager::~CGameObjectManager()
{
	delete m_focusObj;
	delete m_prevTargetObj;
}

void CGameObjectManager::Update()
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

	m_focusObj = getFocusedObj();
	bool lButtonTap = KEY_TAP(KEY::MOUSE_LBUTTON);
	bool lButtonAway = KEY_AWAY(KEY::MOUSE_LBUTTON);
	if (nullptr != m_focusObj)
	{
		m_focusObj->MouseOn();

		if (lButtonTap)
		{
			
			m_focusObj->MouseLButtonDown();
			m_focusObj->m_lButtonDown = true;
		}
		if (lButtonAway)
		{
			m_focusObj->MouseLButtonUp();
			if (m_focusObj->IsLButtonDown())
			{

			}
			m_focusObj->m_lButtonDown = false;

		}
	}
}

CGameObject* CGameObjectManager::getFocusedObj()
{
	CScene* curScene = CSceneManager::GetInst()->GetCurrentScene();
	const vector<CObject*>& backgrounds = curScene->GetObjWithType(m_currentType);

	vector<CObject*>::const_iterator iter = backgrounds.begin();
	vector<CObject*>::const_iterator targetIter = backgrounds.end();

	CGameObject* focusBackObj = m_focusObj;
	bool lButtonTap = KEY_TAP(KEY::MOUSE_LBUTTON);

	//현재 포커스 유지
	if (!lButtonTap)
	{
		return m_focusObj;
	}

	for (; iter != backgrounds.end(); ++iter)
	{
		if (((CGameObject*)(*iter))->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	if (backgrounds.end() == targetIter)
	{
		return nullptr;
	}

	focusBackObj = (CGameObject*)*targetIter;
	curScene->ChangeFocus(targetIter, focusBackObj, m_currentType);

	return focusBackObj;
}

void CGameObjectManager::SetFocusedObj(CGameObject* _obj)
{
	if (nullptr == m_focusObj || _obj == m_focusObj)
	{
		m_focusObj = _obj;
		return;
	}

	m_focusObj = _obj;

	CScene* curScene = CSceneManager::GetInst()->GetCurrentScene();
	const vector<CObject*>& cUIs = curScene->GetObjWithType(GROUP_TYPE::UI);

	vector<CObject*>::const_iterator targetIter = find(cUIs.begin(), cUIs.end(), m_focusObj);

	if (cUIs.end() == targetIter)
	{
		return;
	}

	curScene->ChangeFocus(targetIter, m_focusObj, GROUP_TYPE::UI);
}
