#include "pch.h"
#include "CUI.h"
#include "CCamera.h"
#include "CKeyManager.h"
#include "SelectGDI.h"


CUI::CUI(bool _cameraAffeted)
	:m_parentUI(nullptr)
	,m_lButtonDown(false)
	,m_cameraAffected(_cameraAffeted)
	,m_mouseOn(false)
{
}

CUI::CUI(const CUI& _origin)
	:CObject(_origin)
	, m_cameraAffected(_origin.m_cameraAffected)
	, m_lButtonDown(false)
	, m_mouseOn(false)
	, m_parentUI(nullptr)
{
	for (size_t i = 0; i < _origin.m_childUIs.size(); ++i)
	{
		AddChild(_origin.m_childUIs[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_childUIs);
}

void CUI::Update()
{
	updateChild();
}

void CUI::Render(HDC _dc)
{
	Vec2 pos = GetFinalPos();
	Vec2 scale = GetScale();

	if (m_cameraAffected)
	{
		pos = CCamera::GetInst()->GetRenderPos(pos);
	}
	if (m_lButtonDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(
			_dc,
			int(pos.x),
			int(pos.y),
			int(pos.x + scale.x),
			int(pos.y + scale.y)
		);
	}
	else
	{
		Rectangle(
			_dc,
			int(pos.x),
			int(pos.y),
			int(pos.x + scale.x),
			int(pos.y + scale.y)
		);
	}

	renderChild(_dc);
}

void CUI::FinalUpdate()
{
	CObject::FinalUpdate();
	m_finalPos = GetPos();
	if (nullptr != GetParent())
	{
		Vec2 parentPos = GetParent()->GetFinalPos();
		m_finalPos += parentPos;
	}

	//UI Mouse on check
	MouseOnCheck();

	if (KEY_AWAY(KEY::MOUSE_LBUTTON))
	{
		m_mouseOn = false;
	}

	finalUpdateChild();
}

void CUI::MouseOn()
{
}

void CUI::MouseLButtonDown()
{
}

void CUI::MouseLButtonUp()
{
}

void CUI::MouseLButtonClicked()
{
}

void CUI::MouseOnCheck()
{
	Vec2 mousePos = MOUSE_POS;
	Vec2 scale = GetScale();
	if (m_cameraAffected)
	{
		mousePos = CCamera::GetInst()->GetRenderPos(mousePos);
	}
	if (m_finalPos.x <= mousePos.x && mousePos.x <= m_finalPos.x + scale.x && m_finalPos.y <= mousePos.y && mousePos.y <= m_finalPos.y + scale.y)
	{
		m_mouseOn = true;
	}
	else
	{
		m_mouseOn = false;
	}
}

void CUI::renderChild(HDC _dc)
{
	for (size_t i = 0; i < m_childUIs.size(); ++i)
	{
		m_childUIs[i]->Render(_dc);
	}
}

void CUI::updateChild()
{
	for (size_t i = 0; i < m_childUIs.size(); ++i)
	{
		m_childUIs[i]->Update();
	}
}

void CUI::finalUpdateChild()
{
	for (size_t i = 0; i < m_childUIs.size(); ++i)
	{
		m_childUIs[i]->FinalUpdate();
	}
}
