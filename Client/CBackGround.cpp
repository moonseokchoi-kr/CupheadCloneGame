#include "pch.h"
#include "CBackGround.h"

#include "CTexture.h"

#include "CCamera.h"
#include "CKeyManager.h"
#include "CResourceManager.h"
#include "SelectGDI.h"




CBackGround::CBackGround()
	:m_type(BACKGROUND_TYPE::END)
	,m_currentTex(nullptr)
{
	CResourceManager::GetInst()->LoadTexture(L"canetion_background_sky", L"texture\\cuphead\\background\\canetion_background.bmp");
	CResourceManager::GetInst()->LoadTexture(L"canetion_background_yard", L"texture\\cuphead\\background\\canetion_background_tree.bmp");
	CResourceManager::GetInst()->LoadTexture(L"canetion_background_tree", L"texture\\cuphead\\background\\canetion_tree.bmp");
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BLUE_SKY)] = L"canetion_background_sky";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::TREE)] = L"canetion_background_tree";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::GREEN_YARD)] = L"canetion_background_yard";
}

CBackGround::~CBackGround()
{
}
void CBackGround::Render(HDC _dc)
{
	Vec2 pos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	AlphaBlend(
		_dc,
		(int)pos.x,
		(int)pos.y,
		(int)scale.x,
		(int)scale.y,
		m_currentTex->GetDC(),
		0, 0,
		(int)m_currentTex->Width(),
		(int)m_currentTex->Height(),
		bf
	);
// 	TransparentBlt(
// 		_dc,
// 		pos.x,
// 		pos.y, 
// 		scale.x,
// 		scale.y,
// 		m_currentTex->GetDC(),
// 		0, 0,
// 		m_currentTex->Width(),
// 		m_currentTex->Height(),
// 		RGB(255, 0, 255)
// 	);
	if (IsLButtonDown())
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN_BOLD);
		SelectGDI select1(_dc, BRUSH_TYPE::HOLLOW);
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

void CBackGround::setTexture()
{
	m_currentTex = CResourceManager::GetInst()->FindTexture(m_backGroundArray[TYPE_NUMBER(m_type)]);
	SetScale(Vec2((float)m_currentTex->Width(), (float)m_currentTex->Height()));
}



