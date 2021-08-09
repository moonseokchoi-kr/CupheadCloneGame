#include "pch.h"
#include "CUIManager.h"
#include "CScene.h"
#include "CUI.h"
#include "CSceneManager.h"
#include "CKeyManager.h"

CUIManager::CUIManager()
	:m_focusedUI(nullptr)
{

}
CUIManager::~CUIManager()
{

}
void CUIManager::Update()
{
	//��Ŀ��UI ���ϱ�

	m_focusedUI = GetFocusedUI();
	if (!m_focusedUI)
		return;
	bool lButtonTap = KEY_TAP(KEY::MOUSE_LBUTTON);
	bool lButtonAway = KEY_AWAY(KEY::MOUSE_LBUTTON);

	CUI* targetUI = GetTargetedUI(m_focusedUI);

	if (nullptr != targetUI)
	{
		targetUI->MouseOn();

		if (lButtonTap)
		{
			targetUI->MouseLButtonDown();

			targetUI->m_lButtonDown = true;
		}
		else if (lButtonAway)
		{
			targetUI->MouseLButtonUp();
			if (targetUI->IsLButtonDown())
			{
				targetUI->MouseLButtonClicked();
			}
			targetUI->m_lButtonDown = false;
		}
	}

}

CUI* CUIManager::GetTargetedUI(CUI* _parentUI)
{
	// ���콺�� ���� ����Ű�� �ִ� UI ���ϱ�

	//queue�� �̿��� UI������ ����Ž��(level order)

	static list<CUI*> queue;
	static vector<CUI*> noneTargetUIs;

	queue.clear();
	noneTargetUIs.clear();

	CUI* targetUI = nullptr;
	bool lButtonAway = KEY_AWAY(KEY::MOUSE_LBUTTON);

	queue.push_back(_parentUI);

	while (!queue.empty())
	{
		CUI* ui = queue.front();
		queue.pop_front();

		if (ui->IsMouseOn())
		{
			if (nullptr != targetUI)
			{
				noneTargetUIs.push_back(targetUI);
			}
			targetUI = ui;
		}
		else
		{
			noneTargetUIs.push_back(ui);
		}

		const vector<CUI*>& childs = ui->GetChilds();

		for (size_t i = 0; i < childs.size(); ++i)
		{
			queue.push_back(childs[i]);
		}
	}

	if (lButtonAway)
	{
		for (size_t i = 0; i < noneTargetUIs.size(); ++i)
		{
			noneTargetUIs[i]->m_lButtonDown = false;
		}
	}

	return targetUI;
}

CUI* CUIManager::GetFocusedUI()
{
	
	CScene* curScene = CSceneManager::GetInst()->GetCurrentScene();
	const vector<CObject*>& cUIs = curScene->GetObjWithType(GROUP_TYPE::UI);

	vector<CObject*>::const_iterator iter = cUIs.begin();
	vector<CObject*>::const_iterator targetIter = cUIs.end();
	
	CUI* focusUI = m_focusedUI;
	bool lButtonTap = KEY_TAP(KEY::MOUSE_LBUTTON);

	//���� ��Ŀ�� ����
	if (!lButtonTap)
	{
		return focusUI;
	}

	for (; iter != cUIs.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	if (cUIs.end() == targetIter)
	{
		return nullptr;
	}

	focusUI = (CUI*)*targetIter;
	curScene->ChageFocusUI(targetIter, focusUI);

	return focusUI;
}

void CUIManager::SetFocusedUI(CUI* _ui)
{
	if (nullptr == m_focusedUI || _ui == m_focusedUI)
	{
		m_focusedUI = _ui;
		return;
	}

	m_focusedUI = _ui;

	CScene* curScene = CSceneManager::GetInst()->GetCurrentScene();
	const vector<CObject*>& cUIs = curScene->GetObjWithType(GROUP_TYPE::UI);

	vector<CObject*>::const_iterator targetIter = find(cUIs.begin(), cUIs.end(), m_focusedUI);

	if (cUIs.end() == targetIter)
	{
		return;
	}

	curScene->ChageFocusUI(targetIter, m_focusedUI);

	
}
