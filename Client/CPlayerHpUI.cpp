#include "pch.h"
#include "CPlayerHpUI.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "CPlayer.h"
#include "CCore.h"
#include "SelectGDI.h"
CPlayerHpUI::CPlayerHpUI()
	:CUI(false)
	,m_index(-1)
	,m_owenr(nullptr)
{
	SetScale(Vec2(78.f, 32.f));
	SetPos(Vec2(80.f, 700.f));
	m_tex = CResourceManager::GetInst()->FindTexture(L"PlayerHpTex");
}

CPlayerHpUI::~CPlayerHpUI()
{
}

void CPlayerHpUI::Update()
{
	m_index = m_owenr->GetInfo().health - 1;


	if (m_index == -1)
	{
		m_index = 3;
	}

}

void CPlayerHpUI::Render(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;
	AlphaBlend(
		_dc
		, (int)pos.x
		, (int)pos.y
		, (int)scale.x
		, (int)scale.y
		, m_tex->GetDC()
		, (int)(m_index* scale.x)
		, 0
		, (int)scale.x
		, (int)scale.y
		, bf
	);
}
