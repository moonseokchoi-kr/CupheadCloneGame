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
	CResourceManager::GetInst()->LoadTexture(L"dragon_background_clouds_1", L"texture\\cuphead\\background\\dragon_background_clouds_1.bmp");
	CResourceManager::GetInst()->LoadTexture(L"dragon_background_clouds_2", L"texture\\cuphead\\background\\dragon_background_clouds_2.bmp");
	CResourceManager::GetInst()->LoadTexture(L"dragon_background_clouds_3", L"texture\\cuphead\\background\\dragon_background_clouds_3.bmp");
	CResourceManager::GetInst()->LoadTexture(L"dragon_background_clouds_4", L"texture\\cuphead\\background\\dragon_background_clouds_4.bmp");
	CResourceManager::GetInst()->LoadTexture(L"dragon_background_clouds_5", L"texture\\cuphead\\background\\dragon_background_clouds_5.bmp");
	CResourceManager::GetInst()->LoadTexture(L"dragon_background_clouds_1_night", L"texture\\cuphead\\background\\dragon_background_clouds_1_night.bmp");
	CResourceManager::GetInst()->LoadTexture(L"dragon_background_clouds_2_night", L"texture\\cuphead\\background\\dragon_background_clouds_2_night.bmp");
	CResourceManager::GetInst()->LoadTexture(L"dragon_background_sky_night", L"texture\\cuphead\\background\\dragon_background_sky_night.bmp");
	CResourceManager::GetInst()->LoadTexture(L"dragon_background_sky_normal", L"texture\\cuphead\\background\\dragon_background_sky_normal.bmp");
	
	
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BLUE_SKY)] = L"canetion_background_sky";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::TREE)] = L"canetion_background_tree";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::GREEN_YARD)] = L"canetion_background_yard";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::DARK_CLOUD_1)] = L"dragon_background_clouds_1_night";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::DARK_CLOUD_2)] = L"dragon_background_clouds_2_night";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::NOMAL_CLOUD_1)] = L"dragon_background_clouds_1";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::NOMAL_CLOUD_2)] = L"dragon_background_clouds_2";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::NOMAL_CLOUD_3)] = L"dragon_background_clouds_3";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::NOMAL_CLOUD_4)] = L"dragon_background_clouds_4";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::NOMAL_CLOUD_5)] = L"dragon_background_clouds_5";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::DARK_SKY)] = L"dragon_background_sky_night";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::NOMAL_SKY)] = L"dragon_background_sky_normal";


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



