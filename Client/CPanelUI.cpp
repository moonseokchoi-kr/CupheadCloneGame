#include "pch.h"
#include "CPanelUI.h"
#include "CKeyManager.h"
CPanelUI::CPanelUI(bool _cameraAffeted)
	:CUI(_cameraAffeted)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::MouseOn()
{
	if (IsLButtonDown())
	{
		Vec2 diff = MOUSE_POS - m_dragStart;
		Vec2 curPos = GetPos();

		curPos += diff;

		SetPos(curPos);

		m_dragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLButtonDown()
{
	m_dragStart = MOUSE_POS;
}

void CPanelUI::MouseLButtonUp()
{
}

void CPanelUI::MouseLButtonClicked()
{
}

