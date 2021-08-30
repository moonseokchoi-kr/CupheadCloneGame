#include "pch.h"
#include "CMenuPanel.h"
#include "SelectGDI.h"
#include "CCore.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CBackGround.h"
CMenuPanel::CMenuPanel()
	:CPanelUI(false)
	,m_backGround(nullptr)
	,m_isShow(false)
	,m_menuType(MENU_TYPE::START)
{
	Vec2 resolution = CCore::GetInst()->GetResolution();
	m_tex = CResourceManager::GetInst()->FindTexture(L"VeilTexture");
}

CMenuPanel::~CMenuPanel()
{
	delete m_backGround;
}



void CMenuPanel::Render(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();
	if (CCore::GetInst()->IsDebug())
	{
		Vec2 pos = GetPos();
		Vec2 scale = GetScale();
		SelectGDI gdi(_dc, BRUSH_TYPE::HOLLOW);

		SelectGDI gdi1(_dc, PEN_TYPE::BLACK);
		Rectangle(
			_dc,
			(int)pos.x - scale.x / 2.f,
			(int)pos.y - scale.y / 2.f,
			(int)pos.x + scale.x / 2.f,
			(int)pos.y + scale.y / 2.f
		);

	}
	if (m_backGround != nullptr && m_isShow && MENU_TYPE::PAUSE == m_menuType)
	{
		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = 255*0.35f;

	
		AlphaBlend(
			_dc,
			0,
			0,
			(int)m_tex->Width(),
			(int)m_tex->Height(),
			m_tex->GetDC(),
			0, 0,
			(int)m_tex->Width(),
			(int)m_tex->Height(),
			bf
		);
		m_backGround->Render(_dc);
		for (CUI* child : GetChilds())
		{
			child->Render(_dc);
		}
	}
	else if (MENU_TYPE::START == m_menuType )
	{
		for (CUI* child : GetChilds())
		{
			child->Render(_dc);
		}
	}

}

void CMenuPanel::MouseOn()
{
}

void CMenuPanel::MouseLButtonDown()
{
}

void CMenuPanel::MouseLButtonUp()
{
}

void CMenuPanel::MouseLButtonClicked()
{
}

void CMenuPanel::SetTex(BACKGROUND_TYPE _type)
{
	
	m_backGround->SetType(_type);
	
}


void CMenuPanel::UsePauseUI()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();
	m_backGround = new CBackGround(false);
	m_backGround->SetType(BACKGROUND_TYPE::PAUSE);
	m_backGround->SetPos(resolution / 2.f);
	m_menuType = MENU_TYPE::PAUSE;
}
