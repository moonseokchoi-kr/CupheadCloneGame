#include "pch.h"
#include "CBackGround.h"
#include "CCamera.h"
#include "CKeyManager.h"


#include "SelectGDI.h"

CBackGround::CBackGround()
	:m_lbuttonDown(false)
{
}

CBackGround::~CBackGround()
{
}
void CBackGround::Render(HDC _dc)
{
	Vec2 pos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	Rectangle(
		_dc,
		int(pos.x),
		int(pos.y),
		int(pos.x + scale.x),
		int(pos.y + scale.y)
	);
	if (m_lbuttonDown)
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
}
void CBackGround::Update()
{
	
}

void CBackGround::FinalUpdate()
{

	CObject:: FinalUpdate();
	MouseOnCheck();

}
void CBackGround::MouseOnCheck()
{
	Vec2 mousePos = MOUSE_POS;
	Vec2 pos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	mousePos = CCamera::GetInst()->GetRenderPos(mousePos);

	if (pos.x <= mousePos.x && mousePos.x <= pos.x + scale.x && pos.y <= mousePos.y && mousePos.y <= pos.y + scale.y)
	{
		m_mouseOn = true;
	}
	else
	{
		m_mouseOn = false;
	}
}
void CBackGround::MouseOn()
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

void CBackGround::MouseLButtonDown()
{
	m_dragStart = MOUSE_POS;
}

void CBackGround::MouseLButtonUp()
{
}


